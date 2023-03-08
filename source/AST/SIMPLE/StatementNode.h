#pragma once

#include "../ASTNode.h"
#include <string>

class StatementNode : public ASTNode {
public:
    explicit StatementNode(const uint32_t& stmtNo, const std::string& type);
    uint32_t getStmtNo() const;
private:
    uint32_t stmtNo;
};
