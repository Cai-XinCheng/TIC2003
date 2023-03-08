#pragma once

#include "StatementNode.h"
#include "../Expression/ExpressionNode.h"
#include <string>

class AssignNode : public StatementNode {
public:
    static const std::string& type;
    explicit AssignNode(const uint32_t& stmtNo, const std::string& variableName, const ExpressionNode* expression);
    ~AssignNode() override;
    std::string toString() const override;
    std::string getVariableName() const;
    const ExpressionNode* getExpression() const;

private:
    std::string variableName;
    const ExpressionNode* expression;
};
