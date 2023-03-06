#pragma once

#include "ExpressionParser.h"
#include "./AST/Expression/ConstFactor.h"
#include "./AST/Expression/VariableFactor.h"
#include "./AST/Expression/BinaryTerm.h"
#include "./AST/Expression/BinaryExpression.h"
#include <vector>

ExpressionNode* ExpressionParser::parse(std::vector<std::string>& tokens) const {
    std::vector<Factor*> factors;
    std::vector<std::string> operators;

    unsigned int i = 0;
    std::string token;
    return parseExp(tokens, i);





    //while (i < tokens.size()) {
    //    token = tokens.at(i);
    //    i++;

    //    if (token == "("
    //        || token == "*" || token == "/" || token == "%"
    //        || token == "+" || token == "-") {
    //        operators.push_back(token);
    //    }
    //    else if (token == ")") {
    //        std::vector<Factor*> nestedFactors;
    //        std::vector<std::string> nestedOperators;
    //        while (operators.back() != "(") {
    //            std::string op = operators.back();
    //            operators.pop_back();
    //            nestedOperators.insert(nestedOperators.begin(), op);
    //           
    //            Factor* factor = factors.back();
    //            factors.pop_back();
    //            nestedFactors.insert(nestedFactors.begin(), factor);
    //        }
    //        if (!nestedFactors.empty()) {
    //            Factor* factor = factors.back();
    //            factors.pop_back();
    //            nestedFactors.insert(nestedFactors.begin(), factor);

    //            while (nestedFactors.size() != 1) {
    //                std::string op = nestedOperators.at(0);
    //                nestedOperators.erase(nestedOperators.begin());

    //                Factor* left = nestedFactors.at(0);
    //                Factor* right = nestedFactors.at(1);
    //                nestedFactors.erase(nestedFactors.begin() + 1);

    //                nestedFactors[0] = new BinaryExpression(op, left, right);
    //            }

    //            factors.push_back(nestedFactors.at(0));
    //        }
    //        operators.pop_back();
    //    }
    //    else { // factor
    //        Factor* factor = nullptr;
    //        if (std::isdigit(token[0])) {
    //            int64_t value = std::stoll(token);
    //            factor = new ConstFactor(value);
    //        }
    //        else {
    //            factor = new VariableFactor(token);
    //        }

    //        if (operators.empty()) {
    //            factors.push_back(factor);
    //        }
    //        else {
    //            std::string lastOperator = operators.back();
    //            if (lastOperator == "*" || lastOperator == "/" || lastOperator == "%") {
    //                operators.pop_back();
    //                Factor* lastFactor = factors.back();
    //                Term* term = new BinaryTerm(lastOperator, lastFactor, factor);
    //                factors.back() = term;
    //            }
    //            else { // "(", "+", "-"
    //                factors.push_back(factor);
    //            }
    //        }
    //    }
    //}

    //if (factors.empty()) {
    //    return nullptr;
    //}

    //while (factors.size() != 1) {
    //    std::string op = operators.at(0);
    //    operators.erase(operators.begin());

    //    Factor* left = factors.at(0);
    //    Factor* right = factors.at(1);
    //    factors.erase(factors.begin() + 1);

    //    factors[0] = new BinaryExpression(op, left, right);
    //}
    //return factors.at(0);
}


// factor: var_name | const_value | '(' expr ')'
Factor* ExpressionParser::parseFactor(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    if (token == "(") {
        i++;
        Factor* node = parseExp(tokens, i);
        i++; // ")"
        return node;
    }
    else if (isalpha(token[0])) {
        i++;
        return new VariableFactor(token);
    }
    else if (isalnum(token[0])) {
        int64_t value = static_cast<int64_t>(std::stoll(token));
        i++;
        return new ConstFactor(value);
    }
    return NULL;
}

// term: term '*' factor | term '/' factor | term '%' factor | factor
Factor* ExpressionParser::parseTerm(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    Factor* lhs = parseFactor(tokens, i);
    while (i < tokens.size()) {
        token = tokens.at(i);
        // x*y*z+a -> (x*y)*z+a ; x*(a+b)+c -> (x*(a+b))+c
        if (token == "*" || token == "/" || token == "%") {
            std::string operate = token;
            i++;
            Factor* rhs = parseFactor(tokens, i);
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
Factor* ExpressionParser::parseExp(std::vector<std::string>& tokens, uint32_t& i) const {
    std::string token = tokens.at(i);
    Factor* lhs = parseTerm(tokens, i);
    while (i < tokens.size()) {
        token = tokens.at(i);
        if (token == "+" || token == "-") {
            std::string operate = token;
            i++;
            Factor* rhs = parseTerm(tokens, i);
            lhs = new BinaryExpression(operate, lhs, rhs);
        }
        else {
            break;
        }
    }
    return lhs;
}
