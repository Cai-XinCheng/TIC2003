#include "StatementNode.h"

#include <string>
#include <format>

const std::string& StatementNode::type = "statement";
const std::string& ConExpNode::type = "conExp";

StatementNode::StatementNode(const uint32_t& stmtNo) : ASTNode(type), stmtNo(stmtNo) {}
ConExpNode::ConExpNode(const std::string& operate, ExpressionNode* lhs, ExpressionNode* rhs) : ExpressionNode(type), operate(operate), lhs(lhs), rhs(rhs) {}

AssignNode::~AssignNode() {
    //delete expression;
}

WhileNode::~WhileNode() {
    //delete conExp;
    for (auto& statement : statements) {
        //delete statement;
    }
}

IfNode::~IfNode() {
    //delete conExp;
    for (auto& ifStatement : ifStatements) {
        //delete ifStatement;
    }
    for (auto& elseStatement : elseStatements) {
        //delete elseStatement;
    }
}

std::string StatementNode::toString() const {
    return stmtNode->toString();
}

std::string ReadNode::toString() const {
    return std::format("read {};\n", variableName);
}

std::string PrintNode::toString() const {
    return std::format("print {};\n", variableName);
}

std::string AssignNode::toString() const {
    return std::format("{} = {};\n", variableName, expression->toString());
}

std::string WhileNode::toString() const {
    std::string str = "while (" + conExp->toString() + ") {\n";
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

std::string IfNode::toString() const {
    std::string str = "if (" + conExp->toString() + ") {\n";
    for (auto& stmt : ifStatements) {
        str += stmt->toString();
    }
    str += "} else {\n";
    for (auto& stmt : elseStatements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

std::string CallNode::toString() const {
    return std::format("call {};\n", procedureName);
}


std::vector<std::string> ConExpNode::getVariables() const {
    return ExpressionNode::getVariables({ lhs, rhs });
}

std::vector<int64_t> ConExpNode::getConstants() const {
    return ExpressionNode::getConstants({ lhs, rhs });
}
