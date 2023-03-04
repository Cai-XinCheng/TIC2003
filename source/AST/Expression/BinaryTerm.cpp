#include "BinaryTerm.h"
#include <format>

const std::string& BinaryTerm::nodeType = "BinaryTerm";

BinaryTerm::BinaryTerm(const std::string& op, Factor* left, Factor* right) : Term(nodeType), op(op), left(left), right(right) {
}

BinaryTerm::~BinaryTerm() {
    delete left;
    delete right;
}

std::string BinaryTerm::toString() const {
    return std::format("({} {} {})", left->toString(), op, right->toString());
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