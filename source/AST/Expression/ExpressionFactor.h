#pragma once

#include "Factor.h"
#include "Expression.h"
#include <string>

class ExpressionFactor : public Factor {
public:
    static const std::string& nodeType;
    explicit ExpressionFactor(const Expression* expression);
    ~ExpressionFactor() override;
    std::string toString() const override;
    const Expression* getExpression() const;

private:
    const Expression* expression;
};
