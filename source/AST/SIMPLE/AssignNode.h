#pragma once

#include "../Expression/ExpressionNode.h"
#include "StatementNode.h"
#include <string>

class AssignNode : public StatementNode {
public:
    static const std::string& type;
    explicit AssignNode(const uint32_t& stmtNo, const std::string& variableName, const ExpressionNode* expression, const std::string& indentation = "");
    ~AssignNode() override;
    std::string toString() const override;
    std::string getVariableName() const;
    const ExpressionNode* getExpression() const;

private:
    std::string variableName;
    const ExpressionNode* expression;
};
