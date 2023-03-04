#pragma once

#include "Factor.h"
#include "Expression.h"
#include <string>

class ExpressionFactor : public Factor {
public:
    static const std::string& nodeType;
    explicit ExpressionFactor(Expression* expression);
    ~ExpressionFactor() override;
    std::string toString() const override;
    Expression* getExpression() const;

private:
    Expression* expression;
};
