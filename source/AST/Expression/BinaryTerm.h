#pragma once

#include "Term.h"
#include <string>

class BinaryTerm : public Term {
public:
    static const std::string& nodeType;
    explicit BinaryTerm(const std::string& op, const Factor* left, const Factor* right);
    ~BinaryTerm() override;
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
