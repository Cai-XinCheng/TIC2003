#include "ProgramParser.h"

#include <iostream>

Program ProgramParser::parse() {
    std::vector<ProcedureNode> procedures;
    while (i < tokens.size()) {
        std::string token = tokens.at(i);
        if (token == "procedure") {
            procedures.push_back(parseProcedure());
        }
    }
    return Program(procedures);
}

// function is called when "procedure" is read
ProcedureNode ProgramParser::parseProcedure() {
    i++; // "procedure"
    std::string procedureName = tokens.at(i++);
    i++; // "{"
    std::vector<StatementNode*> statements;
    // read each statement untill end of procedure
    while (tokens.at(i) != "}") {
        StatementNode* statement = parseStatement();
        statements.push_back(statement);
    }
    i++; // "}"
    return ProcedureNode(procedureName, statements);
}

StatementNode* ProgramParser::parseStatement() {
    std::string stmtType = tokens.at(i);
    StatementNode* statementNode = new StatementNode(stmtNo);
    StatementNode* stmtNode;
    if (stmtType == "read") {
        stmtNode = parseRead();
    }
    else if (stmtType == "print") {
        stmtNode = parsePrint();
    }
    else if (stmtType == "while") {
        stmtNode = parseWhile();
    }
    else if (stmtType == "if") {
        stmtNode = parseIf();
    }
    else if (stmtType == "call") {
        stmtNode = parseCall();
    }
    else if (isalpha(stmtType[0])) { // assign
        stmtType = "assign";
        stmtNode = parseAssign();
    }
    else {
        throw std::invalid_argument("ProgramParser: invalid statement type");
    }
    statementNode->setStmtType(stmtType);
    statementNode->setStatementNode(stmtNode);
    return statementNode;
}

ReadNode* ProgramParser::parseRead() {
    i++; // "read"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new ReadNode(stmtNo++, variableName);
}

PrintNode* ProgramParser::parsePrint() {
    i++; // "print"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new PrintNode(stmtNo++, variableName);
}

AssignNode* ProgramParser::parseAssign() {
    // variable
    std::string variableName = tokens.at(i++);
    i++; // "="
    ExpNode* exp = static_cast<ExpNode*>(parseExp());
    i++; // ";
    return new AssignNode(stmtNo++, variableName, exp);
}

WhileNode* ProgramParser::parseWhile() {
    i++; // "while"
    i++; // "("
    // parse condition expression
    ExpNode* lhs = static_cast<ExpNode*>(parseExp());
    std::string op = tokens.at(i++);
    ExpNode* rhs = static_cast<ExpNode*>(parseExp());
    ConExpNode* conExp = new ConExpNode(op, lhs, rhs);
    i++; // ")"
    i++; // "{"
    WhileNode* whileNode = new WhileNode(stmtNo++, conExp);
    // parse while body
    std::vector<StatementNode*> statements;
    while (tokens.at(i) != "}") {
        StatementNode* statement = parseStatement();
        statements.push_back(statement);
    }
    i++; // "}"
    whileNode->setStatements(statements);
    return whileNode;
}

IfNode* ProgramParser::parseIf() {
    i++; // "if"
    i++; // "("
    // parse condition expression
    ExpNode* lhs = static_cast<ExpNode*>(parseExp());
    std::string op = tokens.at(i++);
    ExpNode* rhs = static_cast<ExpNode*>(parseExp());
    ConExpNode* conExp = new ConExpNode(op, lhs, rhs);
    i++; // ")"
    i++; // "then"
    i++; // "{"
    IfNode* ifNode = new IfNode(stmtNo++, conExp);
    // parse if body
    std::vector<StatementNode*> ifStatements;
    std::vector<StatementNode*> elseStatements;
    while (tokens.at(i) != "}") {
        StatementNode* statement = parseStatement();
        ifStatements.push_back(statement);
    }
    i++; // "}"
    i++; // "else"
    i++; // "{"
    // parse else body
    while (tokens.at(i) != "}") {
        StatementNode* statement = parseStatement();
        elseStatements.push_back(statement);
    }
    i++; // "}"
    ifNode->setIfStatements(ifStatements);
    ifNode->setElseStatements(elseStatements);
    return ifNode;
}

CallNode* ProgramParser::parseCall() {
    i++; // "call"
    std::string procedureName = tokens.at(i++);
    i++; // ";"
    return new CallNode(stmtNo++, procedureName);
}


// factor: var_name | const_value | '(' expr ')'
ExpNode* ProgramParser::parseFactor() {
    std::string token = tokens.at(i);
    if (token == "(") {
        i++;
        ExpNode* node = parseExp();
        i++; // ")"
        return node;
    }
    else if (isalpha(token[0])) {
        i++;
        return new VarNode(token);
    }
    else if (isalnum(token[0])) {
        uint32_t value = static_cast<uint32_t>(std::stoul(token));
        i++;
        return new ConstNode(value);
    }
    return NULL;
}

// term: term '*' factor | term '/' factor | term '%' factor | factor
ExpNode* ProgramParser::parseTerm() {
    std::string token = tokens.at(i);
    ExpNode* lhs = parseFactor();
    while (i < tokens.size()) {
        token = tokens.at(i);
        // x*y*z+a -> (x*y)*z+a ; x*(a+b)+c -> (x*(a+b))+c
        if (token == "*" || token == "/" || token == "%") {
            std::string operate = token;
            i++;
            ExpNode* rhs = parseFactor();
            lhs = new ExpNode(operate, lhs, rhs);
        }
        else { // reading ";" or ")" as punctuation
            break;
        }
    }
    // while loop stops when reading ";" or ")" as punctuation
    return lhs;
}

// expr: expr '+' term | expr '-' term | term
ExpNode* ProgramParser::parseExp() {
    std::string token = tokens.at(i);
    ExpNode* lhs = parseTerm();
    while (i < tokens.size()) {
        token = tokens.at(i);
        if (token == "+" || token == "-") {
            std::string operate = token;
            i++;
            ExpNode* rhs = parseTerm();
            lhs = new ExpNode(operate, lhs, rhs);
        }
        else {
            break;
        }
    }
    return lhs;
}


