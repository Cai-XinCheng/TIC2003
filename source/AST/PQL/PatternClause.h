#pragma once

#include "FilterClause.h"
#include <string>

class PatternClause : public FilterClause {
public:
    static const std::string& nodeType;
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
