#pragma once

#include "PatternClause.h"
#include <format>

PatternClause::PatternClause(const std::string& synonymAssignment, const std::string& left, const std::string& right)
    : FilterClause("PatternClause"), synonymAssignment(synonymAssignment), left(left), right(right) {
}

std::string PatternClause::toString() const {
    return std::format("pattern {} ({}, {})", this->synonymAssignment, this->left, this->right);
}

std::string PatternClause::getSynonymAssignment() const {
    return this->synonymAssignment;
}

std::string PatternClause::getLeft() const {
    return this->left;
}

std::string PatternClause::getRight() const {
    return this->right;
}
