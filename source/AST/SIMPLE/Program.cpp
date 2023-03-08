#include "Program.h"

const std::string& Program::type = "program";

Program::Program(const std::vector<const ProcedureNode*>& procedures)
    : ASTNode(type), procedures(procedures) {}

Program::~Program() {
    for (const ProcedureNode* procedure : procedures) {
        delete procedure;
    }
}

std:: string Program::toString() const {
    std::string str = "=========================\n";
    for (const ProcedureNode* procedure : this->procedures) {
        str += procedure->toString();
    }
    str += "=========================\n";
    return str;
}

std::vector<const ProcedureNode*> Program::getProcedures() const {
    return this->procedures;
}
