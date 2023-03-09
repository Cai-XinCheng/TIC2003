#include "AssignNode.h"
#include <format>

const std::string& AssignNode::type = "assign";

AssignNode::AssignNode(const uint32_t& stmtNo, const std::string& variableName, const ExpressionNode* expression, const std::string& indentation)
    : StatementNode(stmtNo, type, indentation), variableName(variableName), expression(expression) {}

AssignNode::~AssignNode() {
    delete expression;
}

std::string AssignNode::toString() const {
    return std::format("{}{} = {};\n", this->getIndentation(), variableName, expression->toString());
}

std::string AssignNode::getVariableName() const {
    return this->variableName;
}

const ExpressionNode* AssignNode::getExpression() const {
    return this->expression;
}
