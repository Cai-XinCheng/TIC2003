#pragma once

#include "Factor.h"

class VariableFactor : public Factor {
public:
    static const std::string& nodeType;
    explicit VariableFactor(const std::string& variableName);
    std::string toString() const override;
    std::vector<std::string> getVariables() const override;
    std::string getVariableName() const;

private:
    std::string variableName;
};
