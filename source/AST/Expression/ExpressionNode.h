#pragma once

#include "../ASTNode.h"
#include <string>

class ExpressionNode : public ASTNode {
public:
    explicit ExpressionNode(const std::string& type);
};
