#include "ExpressionFactor.h"
#include <format>

const std::string& ExpressionFactor::nodeType = "ExpressionFactor";

ExpressionFactor::ExpressionFactor(Expression* expression) : Factor(nodeType), expression(expression) {
}

ExpressionFactor::~ExpressionFactor() {
    delete expression;
}

std::string ExpressionFactor::toString() const {
    return std::format("({})", expression->toString());
}

Expression* ExpressionFactor::getExpression() const {
    return this->expression;
}
