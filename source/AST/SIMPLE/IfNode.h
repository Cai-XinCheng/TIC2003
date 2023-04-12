#pragma once

#include "ConExpNode.h" 
#include "StatementNode.h"
#include <vector>
#include <string>

class IfNode : public StatementNode {
public:
    static const std::string& type;
    explicit IfNode(
        const uint32_t& stmtNo,
        const ConExpNode* conExp,
        const std::vector<const StatementNode*>& ifStatements,
        const std::vector<const StatementNode*>& elseStatements,
        const std::string& indentation = "");
    ~IfNode() override;
    std::string toString() const override;
    const ConExpNode* getConExp() const;
    std::vector<const StatementNode*> getIfStatements() const;
    std::vector<const StatementNode*> getElseStatements() const;

private:
    const ConExpNode* conExp;
    std::vector<const StatementNode*> ifStatements;
    std::vector<const StatementNode*> elseStatements;
};
