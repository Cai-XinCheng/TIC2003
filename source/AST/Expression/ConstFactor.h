#pragma once

#include "Factor.h"

class ConstFactor : public Factor {
public:
    static const std::string& nodeType;
    explicit ConstFactor(const int64_t& value);
    std::string toString() const override;
    std::vector<int64_t> getConstants() const override;
    int64_t getValue() const;

private:
    int64_t value;
};
