#include "ProcedureNode.h"

const std::string& ProcedureNode::type = "procedure";

ProcedureNode::ProcedureNode(const std::string& name, const std::vector<const StatementNode*>& statements)
    : ASTNode(type), procedureName(name), statements(statements) {}

ProcedureNode::~ProcedureNode() {
    for (const StatementNode* statement : statements) {
        delete statement;
    }
}

std::string ProcedureNode::toString() const {
    std::string str = "procedure " + procedureName + "{\n";
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

std::string ProcedureNode::getProcedureName() const {
    return this->procedureName;
}

std::vector<const StatementNode*> ProcedureNode::getStatements() const {
    return this->statements;
}
