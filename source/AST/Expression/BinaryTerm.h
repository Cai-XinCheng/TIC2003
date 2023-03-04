#pragma once

#include "Term.h"
#include <string>

class BinaryTerm : public Term {
public:
    static const std::string& nodeType;
    explicit BinaryTerm(const std::string& op, Factor* left, Factor* right);
    ~BinaryTerm() override;
    std::string toString() const override;
    std::string getOperator() const;
    Factor* getLeft() const;
    Factor* getRight() const;

private:
    std::string op;
    Factor* left;
    Factor* right;
};
