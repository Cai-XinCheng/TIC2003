#pragma once

#include "Expression.h"
#include <string>

class BinaryExpression : public Expression {
public:
    static const std::string& nodeType;
    explicit BinaryExpression(const std::string& op, Factor* left, Factor* right);
    ~BinaryExpression() override;
    std::string toString() const override;
    std::vector<std::string> getVariables() const override;
    std::string getOperator() const;
    Factor* getLeft() const;
    Factor* getRight() const;

private:
    std::string op;
    Factor* left;
    Factor* right;
};
