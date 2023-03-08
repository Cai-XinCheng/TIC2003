#pragma once

#include "StatementNode.h"
#include "../Expression/ExpressionNode.h" 
#include <vector>
#include <string>

class WhileNode : public StatementNode {
public: 
    static const std::string& type;
    explicit WhileNode(const uint32_t& stmtNo, const ExpressionNode* conExp, const std::vector<const StatementNode*>& statements);
    ~WhileNode() override;
    std::string toString() const override;
    const ExpressionNode* getConExp() const;
    std::vector<const StatementNode*> getStatements() const;

private:
    const ExpressionNode* conExp;
    std::vector<const StatementNode*> statements;
};
