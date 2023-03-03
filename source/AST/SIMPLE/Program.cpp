#include "Program.h"

#include <string>
#include <vector>

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
