#pragma once

#include "SelectClause.h"

SelectClause::SelectClause(const std::vector<std::string>& declarations, const std::vector<std::string>& returns, const std::vector<FilterClause>& filters)
    : ASTNode("SelectClause"), declarations(declarations), returns(returns), filters(filters) {
}

void SelectClause::getDeclarations(std::vector<std::string>& declarationsRef) const {
    declarationsRef = this->declarations;
}

void SelectClause::getReturns(std::vector<std::string>& returnsRef) const {
    returnsRef = this->returns;
}

void SelectClause::getFilters(std::vector<FilterClause>& filtersRef) const {
    filtersRef = this->filters;
}
