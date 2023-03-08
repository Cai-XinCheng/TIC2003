#include "ReadNode.h"
#include <format>

const std::string& ReadNode::type = "read";

ReadNode::ReadNode(const uint32_t& stmtNo, const std::string& variableName)
    : StatementNode(stmtNo, type), variableName(variableName) {
}

std::string ReadNode::toString() const {
    return std::format("read {};\n", variableName);
}

std::string ReadNode::getVariableName() const {
    return this->variableName;
}
