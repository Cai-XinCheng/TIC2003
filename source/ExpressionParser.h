#pragma once

#include "AST/Expression/ExpressionNode.h"
#include <vector>
#include <string>

// A class to parse tokens to the AST of Expression
class ExpressionParser {
public:
    ExpressionNode* parse(std::vector<std::string>& tokens) const;
};
