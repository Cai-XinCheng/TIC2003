#pragma once

#include "../ASTNode.h"
#include <string>

class StatementNode : public ASTNode {
public:
    explicit StatementNode(const uint32_t& stmtNo, const std::string& type, const std::string& indentation);
    uint32_t getStmtNo() const;
    std::string getIndentation() const;

private:
    uint32_t stmtNo;
    std::string indentation;
};
