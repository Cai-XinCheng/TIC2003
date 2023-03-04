#include "VariableFactor.h"
#include <format>

const std::string& VariableFactor::nodeType = "VariableFactor";

VariableFactor::VariableFactor(const std::string& variableName) : Factor(nodeType), variableName(variableName) {
}

std::string VariableFactor::toString() const {
    return std::format("({})", variableName);
}


std::string VariableFactor::getVariableName() const {
    return this->variableName;
}
