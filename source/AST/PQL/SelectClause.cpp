#pragma once

#include "SelectClause.h"

SelectClause::SelectClause(const std::vector<Declaration>& declarations, const std::vector<std::string>& returns, const std::vector<FilterClause>& filters)
    : ASTNode("SelectClause"), declarations(declarations), returns(returns), filters(filters) {
}

std::vector<Declaration> SelectClause::getDeclarations() const {
    return this->declarations;
}

std::vector<std::string> SelectClause::getReturns() const {
    return this->returns;
}

std::vector<FilterClause> SelectClause::getFilters() const {
    return this->filters;
}
