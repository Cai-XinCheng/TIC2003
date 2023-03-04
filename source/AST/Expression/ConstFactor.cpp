#include "ConstFactor.h"
#include <format>

const std::string& ConstFactor::nodeType = "ConstFactor";

ConstFactor::ConstFactor(const int64_t& value) : Factor(nodeType), value(value) {
}

std::string ConstFactor::toString() const {
    return std::format("({})", std::to_string(value));
}

int64_t ConstFactor::getValue() const {
    return value;
}
