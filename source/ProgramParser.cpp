#include "AST/SIMPLE/ConExpNode.h"
#include "ProgramParser.h"
#include "ExpressionParser.h"
#include <iostream>

ProgramParser::ProgramParser(const std::vector<std::string>& tokens) : tokens(tokens) {
}

Program ProgramParser::parse() {
    std::vector<const ProcedureNode*> procedures;
    while (i < tokens.size()) {
        std::string token = tokens.at(i);
        if (token == "procedure") {
            procedures.push_back(parseProcedure());
        }
    }
    return Program(procedures);
}

// function is called when "procedure" is read
const ProcedureNode* ProgramParser::parseProcedure() {
    i++; // "procedure"
    std::string procedureName = tokens.at(i++);
    i++; // "{"
    std::vector<const StatementNode*> statements;
    // read each statement untill end of procedure
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement();
        statements.push_back(statement);
    }
    i++; // "}"
    return new ProcedureNode(procedureName, statements);
}

const StatementNode* ProgramParser::parseStatement() {
    std::string stmtType = tokens.at(i);
    if (stmtType == "read") {
        return parseRead();
    }
    else if (stmtType == "print") {
        return parsePrint();
    }
    else if (stmtType == "while") {
        return parseWhile();
    }
    else if (stmtType == "if") {
        return parseIf();
    }
    else if (stmtType == "call") {
        return parseCall();
    }
    else if (isalpha(stmtType[0])) { // assign
        return parseAssign();
    }
    else {
        throw std::invalid_argument("ProgramParser: invalid statement type");
    }
}

const ReadNode* ProgramParser::parseRead() {
    i++; // "read"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new ReadNode(stmtNo++, variableName);
}

const PrintNode* ProgramParser::parsePrint() {
    i++; // "print"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new PrintNode(stmtNo++, variableName);
}

const AssignNode* ProgramParser::parseAssign() {
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

const WhileNode* ProgramParser::parseWhile() {
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
    uint32_t whileNodeStmtNo = stmtNo++;
    // parse while body
    std::vector<const StatementNode*> statements;
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement();
        statements.push_back(statement);
    }

    i++; // "}"
    return new WhileNode(whileNodeStmtNo, conExp, statements);;
}

const IfNode* ProgramParser::parseIf() {
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
    uint32_t ifNodeStmtNo = stmtNo++;
    // parse if body
    std::vector<const StatementNode*> ifStatements;
    std::vector<const StatementNode*> elseStatements;
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement();
        ifStatements.push_back(statement);
    }
    i++; // "}"
    i++; // "else"
    i++; // "{"
    // parse else body
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement();
        elseStatements.push_back(statement);
    }
    i++; // "}"
    return new IfNode(ifNodeStmtNo, conExp, ifStatements, elseStatements);
}

const CallNode* ProgramParser::parseCall() {
    i++; // "call"
    std::string procedureName = tokens.at(i++);
    i++; // ";"
    return new CallNode(stmtNo++, procedureName);
}
