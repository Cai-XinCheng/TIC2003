#pragma once

#include "Expression.h"
#include <string>

class BinaryExpression : public Expression {
public:
    static const std::string& nodeType;
    explicit BinaryExpression(const std::string& op, const Factor* left, const Factor* right);
    ~BinaryExpression() override;
    std::string toString() const override;
    std::vector<std::string> getVariables() const override;
    std::vector<int64_t> getConstants() const override;
    std::string getOperator() const;
    const Factor* getLeft() const;
    const Factor* getRight() const;

private:
    std::string op;
    const Factor* left;
    const Factor* right;
};
