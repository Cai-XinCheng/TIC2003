#pragma once

#include "../ASTNode.h"
#include "StatementNode.h"
#include <vector>
#include <string>

class ProcedureNode;

class Program : public ASTNode {
public:
    explicit Program(std::vector<ProcedureNode>& procedures);
    std::string toString() const override;
    std::vector<ProcedureNode> getProcedures() { return procedures; }
    static const std::string& type;
private:
    std::vector<ProcedureNode> procedures;
};


class ProcedureNode : public ASTNode {
public:
    explicit ProcedureNode(const std::string& name, std::vector<StatementNode*>& statements);
    ~ProcedureNode();
    std::string toString() const override;
    std::string getProcedureName() { return procedureName; }
    std::vector<StatementNode*> getStatements() { return statements; }
    static const std::string& type;
private:
    std::string procedureName;
    std::vector<StatementNode*> statements;
};
