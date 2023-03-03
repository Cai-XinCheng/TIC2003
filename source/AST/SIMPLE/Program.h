#pragma once

#include "../ASTNode.h"
#include "StatementNode.h"
#include <vector>
#include <string>

class ProcedureNode;

class Program : public ASTNode {
public:
    explicit Program(std::vector<ProcedureNode>& procedures) : ASTNode(), procedures(procedures) {};
    std::string toString() const override;
    std::vector<ProcedureNode> getProcedures() { return procedures; }
private:
    std::vector<ProcedureNode> procedures;
};


class ProcedureNode : public ASTNode {
public:
    explicit ProcedureNode(const std::string& name, std::vector<StatementNode*>& statements) 
            : ASTNode(), procedureName(name), statements(statements) {};
    std::string toString() const override;
    std::string getProcedureName() { return procedureName; }
    std::vector<StatementNode*> getStatements() { return statements; }
private:
    std::string procedureName;
    std::vector<StatementNode*> statements;
};
