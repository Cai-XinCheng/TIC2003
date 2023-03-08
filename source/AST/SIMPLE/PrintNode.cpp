#include "PrintNode.h"
#include <format>

const std::string& PrintNode::type = "print";

PrintNode::PrintNode(const uint32_t& stmtNo, const std::string& variableName)
    : StatementNode(stmtNo, type), variableName(variableName) {
}

std::string PrintNode::toString() const {
    return std::format("print {};\n", variableName);
}

std::string PrintNode::getVariableName() const {
    return this->variableName;
}
