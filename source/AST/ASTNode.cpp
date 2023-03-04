#include "ASTNode.h"

ASTNode::ASTNode(const std::string& type) : type(type) {
}

std::string ASTNode::toString() const {
    return this->type;
}

std::string ASTNode::getType() const {
    return this->type;
}

