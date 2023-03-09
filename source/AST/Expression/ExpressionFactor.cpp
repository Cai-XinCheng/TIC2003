#include "ExpressionFactor.h"
#include <format>

const std::string& ExpressionFactor::nodeType = "ExpressionFactor";

ExpressionFactor::ExpressionFactor(const Expression* expression) : Factor(nodeType), expression(expression) {
}

ExpressionFactor::~ExpressionFactor() {
    delete expression;
}

std::string ExpressionFactor::toString() const {
    return std::format("({})", expression->toString());
}

const Expression* ExpressionFactor::getExpression() const {
    return this->expression;
}
