#pragma once

#include "StatementNode.h"
#include "../Expression/ExpressionNode.h" 
#include <vector>
#include <string>

class IfNode : public StatementNode {
public:
    static const std::string& type;
    explicit IfNode(
        const uint32_t& stmtNo,
        const ExpressionNode* conExp,
        const std::vector<const StatementNode*>& ifStatements,
        const std::vector<const StatementNode*>& elseStatements);
    ~IfNode() override;
    std::string toString() const override;
    const ExpressionNode* getConExp() const;
    std::vector<const StatementNode*> getIfStatements() const;
    std::vector<const StatementNode*> getElseStatements() const;

private:
    const ExpressionNode* conExp;
    std::vector<const StatementNode*> ifStatements;
    std::vector<const StatementNode*> elseStatements;
};
