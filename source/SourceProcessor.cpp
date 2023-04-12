#include "SourceProcessor.h"
#include "ProgramParser.h"
#include <stack>
#include <iostream>

void SourceProcessor::process(std::string input) {
    // tokenize the program
    Tokenizer tk;
    std::vector<std::string> tokens;
    tk.tokenize(input, tokens);

    ProgramParser parser(tokens);
    Program program = parser.parse();
    //std::cout << program->toString() << std::endl;

	// initialize the database
	Database::initialize();    
    
    // get procedure list from AST
    std::vector<const ProcedureNode*> procedures = program.getProcedures();
    for (const ProcedureNode* procedure : procedures) {
        processProcedure(procedure);
    }
}

void SourceProcessor::processProcedure(const ProcedureNode* procedureNode) {
    std::string procedureName = procedureNode->getProcedureName();
    Database::insertProcedure(procedureName);
    // get statement linked list
    std::vector<const StatementNode*> statements = procedureNode->getStatements();
    for (unsigned int i = 0; i < statements.size(); i++) {
        processStatement(i, procedureName, statements, 0);
    }
}

void SourceProcessor::processStatement(const int& i, const std::string& procedureName, const std::vector<const StatementNode*>& statements, const uint32_t& nextStmtNo) {
    std::string stmtType = statements.at(i)->getType();
    const StatementNode* stmtNode = statements.at(i);
    uint32_t stmtNo = statements.at(i)->getStmtNo();
    Database::insertStatement(stmtNo, stmtType);

    // process direct parent relation
    if (!parent.empty()) {
        Database::insertParent(stmtNo, parent.top()->StatementNode::getStmtNo());
    }
    // process direct next relation
    if (stmtType != "if") { // specially process next in if case
        if (i != statements.size() - 1) { // not the last statement in the current stmt list
            Database::insertNext(stmtNo, statements.at(i + 1)->getStmtNo());
        }
        else if (nextStmtNo != 0) { // not the end of procedure
            Database::insertNext(stmtNo, nextStmtNo);
        }
    }

    // process statement in different cases
    if (stmtType == "read") {
        std::string variableName = static_cast<const ReadNode*>(stmtNode)->getVariableName();
        Database::insertVariable(variableName, stmtNo, "modify", procedureName);
    }
    else if (stmtType == "print") {
        std::string variableName = static_cast<const PrintNode*>(stmtNode)->getVariableName();
        Database::insertVariable(variableName, stmtNo, "use", procedureName);
    }
    else if (stmtType == "assign") {
        const auto* assignNode = static_cast<const AssignNode*>(stmtNode);
        std::string variableName = assignNode->getVariableName();
        const ExpressionNode* expression = assignNode->getExpression();
        // insert LHS variable into DB
        Database::insertVariable(variableName, stmtNo, "modify", procedureName);
        // process expression
        processExp(expression, stmtNo, procedureName);
        // insert assignemnt into DB
        //std::string expStr = "(" + expression->toString() + ")";
        std::string expStr = expression->toString();
        Database::insertAssignment(stmtNo, variableName, expStr);

    }
    else if (stmtType == "call") {
        std::string calleeName = static_cast<const CallNode*>(stmtNode)->getProcedureName();
        Database::insertCall(stmtNo, procedureName, calleeName);
    }
    else if (stmtType == "while") {
        const WhileNode* whileNode = static_cast<const WhileNode*>(stmtNode);
        parent.push(whileNode);
        const ConExpNode* conExpNode = whileNode->getConExp();
        // process condition expression
        processExp(conExpNode, stmtNo, procedureName);
        // get statement list from while node
        std::vector<const StatementNode*> whileStatements = whileNode->getStatements();
        // process next relation
        if (whileStatements.size() > 0) {
            Database::insertNext(stmtNo, stmtNo + 1);
        }
        for (unsigned int i = 0; i < whileStatements.size(); i++) {
            processStatement(i, procedureName, whileStatements, stmtNo);
        }
        parent.pop();
    }
    else if (stmtType == "if") {
        const IfNode* ifNode = static_cast<const IfNode*>(stmtNode);
        parent.push(ifNode);
        // store next stmtNo of if node
        uint32_t nextStmt = nextStmtNo;
        if (i != statements.size() - 1) {
            nextStmt = statements.at(i + 1)->getStmtNo();
        }

        const ConExpNode* conExpNode = ifNode->getConExp();
        // process condition expression
        processExp(conExpNode, stmtNo, procedureName);
        // get statement list from if node
        std::vector<const StatementNode*> ifStatements = ifNode->getIfStatements();
        // process next relation
        if (ifStatements.size() > 0) {
            Database::insertNext(stmtNo, stmtNo + 1);
        }
        for (unsigned int i = 0; i < ifStatements.size(); i++) {
            processStatement(i, procedureName, ifStatements, nextStmt);
        }
        std::vector<const StatementNode*> elseStatements = ifNode->getElseStatements();
        // process next relation
        if (elseStatements.size() > 0) {
            Database::insertNext(stmtNo, elseStatements.at(0)->getStmtNo());
        }
        for (unsigned int i = 0; i < elseStatements.size(); i++) {
            processStatement(i, procedureName, elseStatements, nextStmt);
        }
        // process next relation of ifNode
        if (ifStatements.size() == 0 || elseStatements.size() == 0) { // if one of the body is empty
            Database::insertNext(stmtNo, nextStmt);
        }
        parent.pop();
    }
    else {
        throw std::invalid_argument("SourceProcessor: invalid statement type");
    }
}


void SourceProcessor::processExp(const ExpressionNode* expression, const uint32_t& stmtNo, const std::string& procedureName) {
    if (expression != nullptr) {
        std::vector<std::string> vars = expression->getVariables();
        for (const std::string& var : vars) {
            Database::insertVariable(var, stmtNo, "use", procedureName);
        }


        std::vector<int64_t> constants = expression->getConstants();
        for (const int64_t& con : constants) {
            auto itCons = cons.find(con);
            if (itCons == cons.end()) { // not declared
                cons.insert(con);
                Database::insertConstant(con);
            }
        }
    }
}
