#include "StatementNode.h"

#include <string>
#include <format>

std::string StatementNode::toString() const {
    return stmtNode->toString();
}

std::string ReadNode::toString() const {
    return std::format("read {};\n", variableName);
}

std::string PrintNode::toString() const {
    return std::format("print {};\n", variableName);
}

std::string AssignNode::toString() const {
    return std::format("{} = {};\n", variableName, expression->toString());
}

std::string WhileNode::toString() const {
    std::string str = "while (" + conExp->toString() + ") {\n";
    for (auto& stmt : statements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

std::string IfNode::toString() const {
    std::string str = "if (" + conExp->toString() + ") {\n";
    for (auto& stmt : ifStatements) {
        str += stmt->toString();
    }
    str += "} else {\n";
    for (auto& stmt : elseStatements) {
        str += stmt->toString();
    }
    str += "}\n";
    return str;
}

std::string CallNode::toString() const {
    return std::format("call {};\n", procedureName);
}
