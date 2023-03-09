#pragma once

#include "StatementNode.h"
#include <string>

class CallNode : public StatementNode {
public:
    static const std::string& type;
    explicit CallNode(const uint32_t& stmtNo, const std::string& procedureName, const std::string& indentation = "");
    std::string toString() const override;
    std::string getProcedureName() const;

private:
    std::string procedureName;
};
