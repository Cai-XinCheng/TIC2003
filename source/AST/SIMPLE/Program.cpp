#include "Program.h"

#include <string>
#include <vector>



const std::string& Program::type = "program";
const std::string& ProcedureNode::type = "procedure";

Program::Program(std::vector<ProcedureNode>& procedures) : ASTNode(type), procedures(procedures) {}
ProcedureNode::ProcedureNode(const std::string& name, std::vector<StatementNode*>& statements) :ASTNode(type), procedureName(name), statements(statements) {}

ProcedureNode::~ProcedureNode() {
    for (auto& statement : statements) {
        //delete statement;
    }
}

std:: string Program::toString() const {
    std::string str = "=========================\n";
    for (auto& procedure : this->procedures) {
        str += procedure.toString();
    }
    str += "=========================\n";
    return str;
}


std::string ProcedureNode::toString() const {
    std::string str = "procedure " + procedureName + "{\n";
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}
