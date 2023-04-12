#pragma once

#include "ConExpNode.h" 
#include "StatementNode.h"
#include <vector>
#include <string>

class WhileNode : public StatementNode {
public: 
    static const std::string& type;
    explicit WhileNode(const uint32_t& stmtNo, const ConExpNode* conExp, const std::vector<const StatementNode*>& statements, const std::string& indentation = "");
    ~WhileNode() override;
    std::string toString() const override;
    const ConExpNode* getConExp() const;
    std::vector<const StatementNode*> getStatements() const;

private:
    const ConExpNode* conExp;
    std::vector<const StatementNode*> statements;
};
