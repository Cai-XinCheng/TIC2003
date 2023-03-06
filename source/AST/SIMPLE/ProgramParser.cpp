#include "ProgramParser.h"
#include "../../ExpressionParser.h"
#include "../Expression/BinaryExpression.h"
#include <iostream>


ExpressionParser ep;


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

    // read expression into temp tokens
    std::string tempToken;
    std::vector<std::string> tempTokens;
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != ";");
    tempTokens.pop_back();
    ExpressionNode* exp = ep.parse(tempTokens);
    i--;
    i++; // ";"
    return new AssignNode(stmtNo++, variableName, exp);
}

WhileNode* ProgramParser::parseWhile() {
    i++; // "while"
    i++; // "("

    // parse condition expression
    // read expression into temp tokens
    std::string tempToken;
    std::vector<std::string> tempTokens;
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != "<"
        && tempToken != ">"
        && tempToken != "="
        && tempToken != "!="
        && tempToken != ">="
        && tempToken != "<="
        && tempToken != "==");
    tempTokens.pop_back();
    i--;
    ExpressionNode* lhs = ep.parse(tempTokens);
    std::string op = tokens.at(i++);
    tempTokens.clear();
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != ")");
    tempTokens.pop_back();
    i--;
    ExpressionNode* rhs = ep.parse(tempTokens);
    ExpressionNode* conExp = new ConExpNode(op, lhs, rhs);
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
    // read expression into temp tokens
    std::string tempToken = tokens.at(i);
    std::vector<std::string> tempTokens;
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != "<"
        && tempToken != ">"
        && tempToken != "="
        && tempToken != "!="
        && tempToken != ">="
        && tempToken != "<="
        && tempToken != "==");
    tempTokens.pop_back();
    i--;
    ExpressionNode* lhs = ep.parse(tempTokens);
    std::string op = tokens.at(i++);
    tempTokens.clear();
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != ")");
    tempTokens.pop_back();
    i--;
    ExpressionNode* rhs = ep.parse(tempTokens);
    ExpressionNode* conExp = new ConExpNode(op, lhs, rhs);
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

