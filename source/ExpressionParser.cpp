#pragma once

#include "ExpressionParser.h"
#include "./AST/Expression/ConstFactor.h"
#include "./AST/Expression/VariableFactor.h"
#include "./AST/Expression/BinaryTerm.h"
#include "./AST/Expression/BinaryExpression.h"
#include <vector>
#include <iostream>
#include <sstream>

const ExpressionNode* ExpressionParser::parse(std::vector<std::string>& tokens) const {
    std::vector<Factor*> factors;
    std::vector<std::string> operators;

    unsigned int i = 0;
    std::string token;
    return parseExp(tokens, i);
}


// factor: var_name | const_value | '(' expr ')'
const Factor* ExpressionParser::parseFactor(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    if (token == "(") {
        i++;
        const Factor* node = parseExp(tokens, i);
        i++; // ")"
        return node;
    }
    else if (isalpha(token[0])) {
        i++;
        return new VariableFactor(token);
    }
    else if (isalnum(token[0])) {
        int64_t value;
        std::istringstream iss(token);
        iss >> value;
        i++;
        return new ConstFactor(value);
    }
    return nullptr;
}

// term: term '*' factor | term '/' factor | term '%' factor | factor
const Factor* ExpressionParser::parseTerm(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    const Factor* lhs = parseFactor(tokens, i);
    while (i < tokens.size()) {
        token = tokens.at(i);
        // x*y*z+a -> (x*y)*z+a ; x*(a+b)+c -> (x*(a+b))+c
        if (token == "*" || token == "/" || token == "%") {
            std::string operate = token;
            i++;
            const Factor* rhs = parseFactor(tokens, i);
            lhs = new BinaryTerm(operate, lhs, rhs);
        }
        else { // reading ";" or ")" as punctuation
            break;
        }
    }
    // while loop stops when reading ";" or ")" as punctuation
    return lhs;
}

// expr: expr '+' term | expr '-' term | term
const Factor* ExpressionParser::parseExp(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    const Factor* lhs = parseTerm(tokens, i);
    while (i < tokens.size()) {
        token = tokens.at(i);
        if (token == "+" || token == "-") {
            std::string operate = token;
            i++;
            const Factor* rhs = parseTerm(tokens, i);
            lhs = new BinaryExpression(operate, lhs, rhs);
        }
        else {
            break;
        }
    }
    return lhs;
}
