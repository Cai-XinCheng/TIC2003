#pragma once

#include "Factor.h"
#include <string>

class VariableFactor : public Factor {
public:
    static const std::string& nodeType;
    explicit VariableFactor(const std::string& variableName);
    std::string toString() const override;
    std::string getVariableName() const;

private:
    std::string variableName;
};
