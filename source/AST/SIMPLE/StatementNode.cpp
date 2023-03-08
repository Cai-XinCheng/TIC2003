#include "StatementNode.h"
#include <format>

StatementNode::StatementNode(const uint32_t& stmtNo, const std::string& type)
    : ASTNode(type), stmtNo(stmtNo) {
}

uint32_t StatementNode::getStmtNo() const {
    return this->stmtNo;
}
