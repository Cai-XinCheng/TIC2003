#include "ProgramParser.h"
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
        const StatementNode* statement = parseStatement("  ");
        statements.push_back(statement);
    }
    i++; // "}"
    return new ProcedureNode(procedureName, statements);
}

const StatementNode* ProgramParser::parseStatement(const std::string& indentation) {
    std::string stmtType = tokens.at(i);
    if (stmtType == "read") {
        return parseRead(indentation);
    }
    else if (stmtType == "print") {
        return parsePrint(indentation);
    }
    else if (stmtType == "while") {
        return parseWhile(indentation);
    }
    else if (stmtType == "if") {
        return parseIf(indentation);
    }
    else if (stmtType == "call") {
        return parseCall(indentation);
    }
    else if (isalpha(stmtType[0])) { // assign
        return parseAssign(indentation);
    }
    else {
        throw std::invalid_argument("ProgramParser: invalid statement type");
    }
}

const ReadNode* ProgramParser::parseRead(const std::string& indentation) {
    i++; // "read"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new ReadNode(stmtNo++, variableName, indentation);
}

const PrintNode* ProgramParser::parsePrint(const std::string& indentation) {
    i++; // "print"
    std::string variableName = tokens.at(i++);
    i++; // ";"
    return new PrintNode(stmtNo++, variableName, indentation);
}

const AssignNode* ProgramParser::parseAssign(const std::string& indentation) {
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
    const ExpressionNode* exp = ep.parse(tempTokens);
    i--;
    i++; // ";"
    return new AssignNode(stmtNo++, variableName, exp, indentation);
}

const WhileNode* ProgramParser::parseWhile(const std::string& indentation) {
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
    const ExpressionNode* lhs = ep.parse(tempTokens);
    std::string op = tokens.at(i++);
    tempTokens.clear();
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != "{");
    tempTokens.pop_back();
    tempToken.pop_back();
    i--;
    i--;
    const ExpressionNode* rhs = ep.parse(tempTokens);
    const ExpressionNode* conExp = new ConExpNode(op, lhs, rhs);
    i++; // ")"

    i++; // "{"
    uint32_t whileNodeStmtNo = stmtNo++;
    // parse while body
    std::vector<const StatementNode*> statements;
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement(indentation + "  ");
        statements.push_back(statement);
    }

    i++; // "}"
    return new WhileNode(whileNodeStmtNo, conExp, statements, indentation);
}

const IfNode* ProgramParser::parseIf(const std::string& indentation) {
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
    const ExpressionNode* lhs = ep.parse(tempTokens);
    std::string op = tokens.at(i++);
    tempTokens.clear();
    do {
        tempToken = tokens.at(i);
        tempTokens.push_back(tempToken);
        i++;
    } while (tempToken != "then");
    tempTokens.pop_back();
    tempToken.pop_back();
    i--;
    i--;
    const ExpressionNode* rhs = ep.parse(tempTokens);
    const ExpressionNode* conExp = new ConExpNode(op, lhs, rhs);
    i++; // ")"
    i++; // "then"
    i++; // "{"
    uint32_t ifNodeStmtNo = stmtNo++;
    // parse if body
    std::vector<const StatementNode*> ifStatements;
    std::vector<const StatementNode*> elseStatements;
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement(indentation + "  ");
        ifStatements.push_back(statement);
    }
    i++; // "}"
    i++; // "else"
    i++; // "{"
    // parse else body
    while (tokens.at(i) != "}") {
        const StatementNode* statement = parseStatement(indentation + "  ");
        elseStatements.push_back(statement);
    }
    i++; // "}"
    return new IfNode(ifNodeStmtNo, conExp, ifStatements, elseStatements, indentation);
}

const CallNode* ProgramParser::parseCall(const std::string& indentation) {
    i++; // "call"
    std::string procedureName = tokens.at(i++);
    i++; // ";"
    return new CallNode(stmtNo++, procedureName, indentation);
}

