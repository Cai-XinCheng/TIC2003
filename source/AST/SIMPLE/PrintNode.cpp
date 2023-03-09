#include "PrintNode.h"
#include <format>

const std::string& PrintNode::type = "print";

PrintNode::PrintNode(const uint32_t& stmtNo, const std::string& variableName, const std::string& indentation)
    : StatementNode(stmtNo, type, indentation), variableName(variableName) {
}

std::string PrintNode::toString() const {
    return std::format("{}print {};\n", this->getIndentation(), variableName);
}

std::string PrintNode::getVariableName() const {
    return this->variableName;
}
