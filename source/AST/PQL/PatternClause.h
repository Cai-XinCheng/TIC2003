#pragma once

#include "FilterClause.h"
#include <string>

class PatternClause : public FilterClause {
public:
    explicit PatternClause(const std::string& synonymAssignment, const std::string& left, const std::string& right);
    std::string getSynonymAssignment() const;
    std::string getLeft() const;
    std::string getRight() const;

private:
    std::string synonymAssignment;
    std::string left;
    std::string right;
};
