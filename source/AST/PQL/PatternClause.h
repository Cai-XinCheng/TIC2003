#pragma once

#include "FilterClause.h"
#include <string>

class PatternClause : public FilterClause {
public:
    explicit PatternClause(const std::string& left, const std::string& right);
    void getLeft(std::string& leftRef) const;
    void getRight(std::string& rightRef) const;

private:
    std::string left;
    std::string right;
};
