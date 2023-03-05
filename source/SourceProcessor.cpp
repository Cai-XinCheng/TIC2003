#include "SourceProcessor.h"
#include "./AST/ASTNode.h"
#include "./AST/SIMPLE/ProgramParser.h"
#include <stack>
#include <iostream>

void processProcedure(ProcedureNode procedureNode);
void processStatement(int i, const std::string& procedureName, std::vector<StatementNode*> statements, uint32_t nextStmtNo);
void processExp(ExpNode* expression, uint32_t stmtNo, std::string procedureName);

std::set<uint32_t> cons;
std::set<std::string> vars;
std::stack<StatementNode*> parent;

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
    std::vector<ProcedureNode> procedures = program.getProcedures();
    for (auto& procedure : procedures) {
        processProcedure(procedure);
    }
}

void processProcedure(ProcedureNode procedureNode) {
    std::string procedureName = procedureNode.getProcedureName();
    Database::insertProcedure(procedureName);
    // get statement linked list
    std::vector<StatementNode*> statements = procedureNode.getStatements();
    for (unsigned int i = 0; i < statements.size(); i++) {
        processStatement(i, procedureName, statements, 0);
    }
}

void processStatement(int i,const std::string& procedureName, std::vector<StatementNode*> statements, uint32_t nextStmtNo) {
    std::string stmtType = statements.at(i)->getStmtType();
    StatementNode* stmtNode = statements.at(i)->getStmtNode();
    uint32_t stmtNo = statements.at(i)->getStmtNo();
    Database::insertStatement(stmtNo, stmtType);

    // process direct parent relation
    if (stmtType == "read" || stmtType == "print" || stmtType == "assign" || stmtType == "call") {
        if (!parent.empty()) {
            Database::insertParent(stmtNo, parent.top()->StatementNode::getStmtNo());
        }
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
        std::string variableName = static_cast<ReadNode*>(stmtNode)->getVariableName();
        Database::insertVariable(variableName, stmtNo, "modify", procedureName);
    }
    else if (stmtType == "print") {
        std::string variableName = static_cast<PrintNode*>(stmtNode)->getVariableName();
        Database::insertVariable(variableName, stmtNo, "use", procedureName);
    }
    else if (stmtType == "assign") {
        AssignNode* assignNode = static_cast<AssignNode*>(stmtNode);
        std::string variableName = assignNode->getVariableName();
        ExpNode* expression = assignNode->getExpression();
        // insert LHS variable into DB
        Database::insertVariable(variableName, stmtNo, "modify", procedureName);
        // process expression
        processExp(expression, stmtNo, procedureName);
        vars.clear();
        // insert assignemnt into DB
        std::string expStr = "(" + expression->toString() + ")";
        Database::insertAssignment(stmtNo, variableName, expStr);

    }
    else if (stmtType == "call") {
        std::string calleeName = static_cast<CallNode*>(stmtNode)->getProcedureName();
        Database::insertCall(stmtNo, procedureName, calleeName);
    }
    else if (stmtType == "while") {
        WhileNode* whileNode = static_cast<WhileNode*>(stmtNode);
        parent.push(whileNode);
        ConExpNode* conExpNode = static_cast<ConExpNode*>(whileNode->getConExp());
        // process condition expression
        processExp(conExpNode, stmtNo, procedureName);
        vars.clear();
        // get statement list from while node
        std::vector<StatementNode*> whileStatements = whileNode->getStatements();
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
        IfNode* ifNode = static_cast<IfNode*>(stmtNode);
        parent.push(ifNode);
        // store next stmtNo of if node
        uint32_t nextStmtNo = statements.at(i + 1)->getStmtNo();

        ConExpNode* conExpNode = static_cast<ConExpNode*>(ifNode->getConExp());
        // process condition expression
        processExp(conExpNode, stmtNo, procedureName);
        vars.clear();
        // get statement list from if node
        std::vector<StatementNode*> ifStatements = ifNode->getIfStatements();
        // process next relation
        if (ifStatements.size() > 0) {
            Database::insertNext(stmtNo, stmtNo + 1);
        }
        for (unsigned int i = 0; i < ifStatements.size(); i++) {
            processStatement(i, procedureName, ifStatements, nextStmtNo);
        }
        std::vector<StatementNode*> elseStatements = ifNode->getElseStatements();
        // process next relation
        if (elseStatements.size() > 0) {
            Database::insertNext(stmtNo, elseStatements.at(0)->getStmtNo());
        }
        for (unsigned int i = 0; i < elseStatements.size(); i++) {
            processStatement(i, procedureName, elseStatements, nextStmtNo);
        }
        // process next relation of ifNode
        if (ifStatements.size() == 0 || elseStatements.size() == 0) { // if one of the body is empty
            Database::insertNext(stmtNo, nextStmtNo);
        }
        parent.pop();
    }
    else {
        throw std::invalid_argument("SourceProcessor: invalid statement type");
    }
}


void processExp(ExpNode* expression, uint32_t stmtNo, std::string procedureName) {
    if (expression != NULL) {
        if (typeid(*expression) == typeid(VarNode)) {
            std::string var = static_cast<VarNode*>(expression)->getVariableName();
            auto itVars = vars.find(var);
            if (itVars == vars.end()) { // not declared
                vars.insert(var);
                Database::insertVariable(var, stmtNo, "use", procedureName);
            }
        }
        else if (typeid(*expression) == typeid(ConstNode)) {
            uint32_t value = static_cast<ConstNode*>(expression)->getValue();
            auto itCons = cons.find(value);
            if (itCons == cons.end()) { // not declared
                cons.insert(value);
                Database::insertConstant(static_cast<int64_t>(value));
            }
        }
        else {
            processExp(expression->ExpNode::getLhs(), stmtNo, procedureName);
            processExp(expression->ExpNode::getRhs(), stmtNo, procedureName);
        }
    }
}

