#include "CallNode.h"
#include <format>

const std::string& CallNode::type = "call";

CallNode::CallNode(const uint32_t& stmtNo, const std::string& procedureName)
    : StatementNode(stmtNo, type), procedureName(procedureName) {
}

std::string CallNode::toString() const {
    return std::format("call {};\n", procedureName);
}

std::string CallNode::getProcedureName() const {
    return this->procedureName;
}
