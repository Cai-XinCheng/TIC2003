#include "BinaryTerm.h"
#include <format>

const std::string& BinaryTerm::nodeType = "BinaryTerm";

BinaryTerm::BinaryTerm(const std::string& op, Factor* left, Factor* right) : Term(nodeType), op(op), left(left), right(right) {
}

BinaryTerm::~BinaryTerm() {
    //delete left;
    //delete right;
}

std::string BinaryTerm::toString() const {
    return std::format("({} {} {})", left->toString(), op, right->toString());
}

std::vector<std::string> BinaryTerm::getVariables() const {
    return ExpressionNode::getVariables({ left, right });
}

std::vector<int64_t> BinaryTerm::getConstants() const {
    return ExpressionNode::getConstants({ left, right });
}

std::string BinaryTerm::getOperator() const {
    return this->op;
}

Factor* BinaryTerm::getLeft() const {
    return this->left;
}

Factor* BinaryTerm::getRight() const {
    return this->right;
}
