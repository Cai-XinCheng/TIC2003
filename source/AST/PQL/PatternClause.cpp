#pragma once

#include "PatternClause.h"

PatternClause::PatternClause(const std::string& left, const std::string& right)
    : FilterClause("PatternClause"), left(left), right(right) {
}

void PatternClause::getLeft(std::string& leftRef) const {
    leftRef = this->left;
}

void PatternClause::getRight(std::string & rightRef) const {
    rightRef = this->right;
}
