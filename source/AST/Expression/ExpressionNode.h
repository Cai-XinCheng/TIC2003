#pragma once

#include "../ASTNode.h"
#include <string>
#include <vector>

class ExpressionNode : public ASTNode {
public:
    explicit ExpressionNode(const std::string& type);
    static std::vector<std::string> getVariables(const std::vector<const ExpressionNode*>& expressionNodes);
    virtual std::vector<std::string> getVariables() const;
};
