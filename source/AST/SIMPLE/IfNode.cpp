#include "IfNode.h"
#include <format>

const std::string& IfNode::type = "if";

IfNode::IfNode(
    const uint32_t& stmtNo,
    const ExpressionNode* conExp,
    const std::vector<const StatementNode*>& ifStatements,
    const std::vector<const StatementNode*>& elseStatements)
    : StatementNode(stmtNo, type), conExp(conExp), ifStatements(ifStatements), elseStatements(elseStatements) {
}

IfNode::~IfNode() {
    delete conExp;
    for (const StatementNode* ifStatement : ifStatements) {
        delete ifStatement;
    }
    for (const StatementNode* elseStatement : elseStatements) {
        delete elseStatement;
    }
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

const ExpressionNode* IfNode::getConExp() const {
    return this->conExp;
}

std::vector<const StatementNode*> IfNode::getIfStatements() const {
    return this->ifStatements;
}

std::vector<const StatementNode*> IfNode::getElseStatements() const {
    return this->elseStatements;
}
