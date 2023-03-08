#include "WhileNode.h"
#include <format>

const std::string& WhileNode::type = "while";

WhileNode::WhileNode(const uint32_t& stmtNo, const ExpressionNode* conExp, const std::vector<const StatementNode*>& statements)
    : StatementNode(stmtNo, type), conExp(conExp), statements(statements) {
}

WhileNode::~WhileNode() {
    delete conExp;
    for (const StatementNode* statement : statements) {
        delete statement;
    }
}

std::string WhileNode::toString() const {
    std::string str = "while (" + conExp->toString() + ") {\n";
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

const ExpressionNode* WhileNode::getConExp() const {
    return this->conExp;
}

std::vector<const StatementNode*> WhileNode::getStatements() const {
    return this->statements;
}
