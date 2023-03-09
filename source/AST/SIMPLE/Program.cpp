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
    std::string str = "";
    for (size_t i = 0; i < procedures.size(); i++) {
        if (i != 0) {
            str += "\n";
        }
        str += procedures[i]->toString();
    }
    return str;
}

std::vector<const ProcedureNode*> Program::getProcedures() const {
    return this->procedures;
}
