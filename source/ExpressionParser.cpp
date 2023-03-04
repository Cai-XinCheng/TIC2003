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
    while (i < tokens.size()) {
        token = tokens.at(i);
        i++;

        if (token == "("
            || token == "*" || token == "/" || token == "%"
            || token == "+" || token == "-") {
            operators.push_back(token);
        }
        else if (token == ")") {
            std::vector<Factor*> nestedFactors;
            std::vector<std::string> nestedOperators;
            while (operators.back() != "(") {
                std::string op = operators.back();
                operators.pop_back();
                nestedOperators.insert(nestedOperators.begin(), op);
               
                Factor* factor = factors.back();
                factors.pop_back();
                nestedFactors.insert(nestedFactors.begin(), factor);
            }
            if (!nestedFactors.empty()) {
                Factor* factor = factors.back();
                factors.pop_back();
                nestedFactors.insert(nestedFactors.begin(), factor);

                while (nestedFactors.size() != 1) {
                    std::string op = nestedOperators.at(0);
                    nestedOperators.erase(nestedOperators.begin());

                    Factor* left = nestedFactors.at(0);
                    Factor* right = nestedFactors.at(1);
                    nestedFactors.erase(nestedFactors.begin() + 1);

                    nestedFactors[0] = new BinaryExpression(op, left, right);
                }

                factors.push_back(nestedFactors.at(0));
            }
            operators.pop_back();
        }
        else { // factor
            Factor* factor = nullptr;
            if (std::isdigit(token[0])) {
                int64_t value = std::stoll(token);
                factor = new ConstFactor(value);
            }
            else {
                factor = new VariableFactor(token);
            }

            if (operators.empty()) {
                factors.push_back(factor);
            }
            else {
                std::string lastOperator = operators.back();
                if (lastOperator == "*" || lastOperator == "/" || lastOperator == "%") {
                    operators.pop_back();
                    Factor* lastFactor = factors.back();
                    Term* term = new BinaryTerm(lastOperator, lastFactor, factor);
                    factors.back() = term;
                }
                else { // "(", "+", "-"
                    factors.push_back(factor);
                }
            }
        }
    }

    if (factors.empty()) {
        return nullptr;
    }

    while (factors.size() != 1) {
        std::string op = operators.at(0);
        operators.erase(operators.begin());

        Factor* left = factors.at(0);
        Factor* right = factors.at(1);
        factors.erase(factors.begin() + 1);

        factors[0] = new BinaryExpression(op, left, right);
    }
    return factors.at(0);
}
