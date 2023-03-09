#pragma once

#include "../Expression/ExpressionNode.h" 
#include "StatementNode.h"
#include <vector>
#include <string>

class WhileNode : public StatementNode {
public: 
    static const std::string& type;
    explicit WhileNode(const uint32_t& stmtNo, const ExpressionNode* conExp, const std::vector<const StatementNode*>& statements, const std::string& indentation = "");
    ~WhileNode() override;
    std::string toString() const override;
    const ExpressionNode* getConExp() const;
    std::vector<const StatementNode*> getStatements() const;

private:
    const ExpressionNode* conExp;
    std::vector<const StatementNode*> statements;
};
