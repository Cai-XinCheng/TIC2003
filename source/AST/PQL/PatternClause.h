#pragma once

#include "FilterClause.h"
#include <string>
#include <format>

class PatternClause : public FilterClause {
public:
    explicit PatternClause(const std::string& synonymAssignment, const std::string& left, const std::string& right);
    std::string toString() const override;
    std::string getSynonymAssignment() const;
    std::string getLeft() const;
    std::string getRight() const;

private:
    std::string synonymAssignment;
    std::string left;
    std::string right;
};
