#include "BinaryExpression.h"
#include <format>

const std::string& BinaryExpression::nodeType = "BinaryExpression";

BinaryExpression::BinaryExpression(const std::string& op, Factor* left, Factor* right) : Expression(nodeType), op(op), left(left), right(right) {
}

BinaryExpression::~BinaryExpression() {
    delete left;
    delete right;
}

std::string BinaryExpression::toString() const {
    return std::format("({} {} {})", left->toString(), op, right->toString());
}

std::string BinaryExpression::getOperator() const {
    return this->op;
}

Factor* BinaryExpression::getLeft() const {
    return this->left;
}

Factor* BinaryExpression::getRight() const {
    return this->right;
}
