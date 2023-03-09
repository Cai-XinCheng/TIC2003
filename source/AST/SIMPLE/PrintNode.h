#pragma once

#include "StatementNode.h"
#include <string>

class PrintNode : public StatementNode {
public:
    static const std::string& type;
    explicit PrintNode(const uint32_t& stmtNo, const std::string& variableName, const std::string& indentation = "");
    std::string toString() const override;
    std::string getVariableName() const;

private:
    std::string variableName;
};
