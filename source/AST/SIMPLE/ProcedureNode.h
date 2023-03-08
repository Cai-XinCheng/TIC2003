#pragma once

#include "StatementNode.h"
#include <vector>
#include <string>

class ProcedureNode : public ASTNode {
public:
    static const std::string& type;
    explicit ProcedureNode(const std::string& name, const std::vector<const StatementNode*>& statements);
    ~ProcedureNode() override;
    std::string toString() const override;
    std::string getProcedureName() const;
    std::vector<const StatementNode*> getStatements() const;

private:
    std::string procedureName;
    std::vector<const StatementNode*> statements;
};
