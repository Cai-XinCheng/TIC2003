#include "ASTNode.h"

ASTNode::ASTNode(const std::string& type) : type(type) {
}

void ASTNode::getType(std::string& typeRef) const {
    typeRef = this->type;
}
