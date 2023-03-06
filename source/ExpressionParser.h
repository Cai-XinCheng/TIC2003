#pragma once

#include "AST/Expression/ExpressionNode.h"
#include "AST/Expression/Factor.h"
#include <vector>
#include <string>

// A class to parse tokens to the AST of Expression
class ExpressionParser {
public:
    ExpressionNode* parse(std::vector<std::string>& tokens) const;
    Factor* parseExp(std::vector<std::string>& tokens, uint32_t& i) const;
    Factor* parseTerm(std::vector<std::string>& tokens, uint32_t& i) const;
    Factor* parseFactor(std::vector<std::string>& tokens, uint32_t& i) const;
};
