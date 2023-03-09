#pragma once

#include "../Expression/ExpressionNode.h" 
#include <string>

class ConExpNode : public ExpressionNode {
public:
    static const std::string& type;
    explicit ConExpNode(const std::string& operate, const ExpressionNode* lhs, const ExpressionNode* rhs);
    ~ConExpNode() override;
    std::string toString() const override;
    std::vector<std::string> getVariables() const override;
    std::vector<int64_t> getConstants() const override;
private:
    std::string operate;
    const ExpressionNode* lhs;
    const ExpressionNode* rhs;
};
