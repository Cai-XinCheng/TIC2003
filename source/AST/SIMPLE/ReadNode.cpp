#include "ReadNode.h"
#include <format>

const std::string& ReadNode::type = "read";

ReadNode::ReadNode(const uint32_t& stmtNo, const std::string& variableName, const std::string& indentation)
    : StatementNode(stmtNo, type, indentation), variableName(variableName) {
}

std::string ReadNode::toString() const {
    return std::format("{}read {};\n", this->getIndentation(), variableName);
}

std::string ReadNode::getVariableName() const {
    return this->variableName;
}
