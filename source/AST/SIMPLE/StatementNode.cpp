#include "StatementNode.h"
#include <format>

StatementNode::StatementNode(const uint32_t& stmtNo, const std::string& type, const std::string& indentation = "")
    : ASTNode(type), stmtNo(stmtNo), indentation(indentation) {
}

uint32_t StatementNode::getStmtNo() const {
    return this->stmtNo;
}

std::string StatementNode::getIndentation() const {
    return this->indentation;
}


