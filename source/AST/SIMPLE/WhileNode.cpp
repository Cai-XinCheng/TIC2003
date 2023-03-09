#include "WhileNode.h"
#include <format>

const std::string& WhileNode::type = "while";

WhileNode::WhileNode(const uint32_t& stmtNo, const ExpressionNode* conExp, const std::vector<const StatementNode*>& statements, const std::string& indentation)
    : StatementNode(stmtNo, type, indentation), conExp(conExp), statements(statements) {
}

WhileNode::~WhileNode() {
    delete conExp;
    for (const StatementNode* statement : statements) {
        delete statement;
    }
}

std::string WhileNode::toString() const {
    std::string str = std::format("{}while ({}) {{\n", this->getIndentation(), conExp->toString());
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += std::format("{}}}\n", this->getIndentation());
    return str;
}

const ExpressionNode* WhileNode::getConExp() const {
    return this->conExp;
}

std::vector<const StatementNode*> WhileNode::getStatements() const {
    return this->statements;
}
