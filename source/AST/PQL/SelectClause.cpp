#pragma once

#include "SelectClause.h"
#include <format>
#include <numeric>

SelectClause::SelectClause(const std::vector<Declaration>& declarations, const std::vector<std::string>& returns, const std::vector<FilterClause*>& filters)
    : ASTNode("SelectClause"), declarations(declarations), returns(returns), filters(filters) {
}

SelectClause::~SelectClause() {
    for (FilterClause* filter : this->filters) {
        delete filter;
    }
}

std::string SelectClause::toString() const {
    std::string declarationLine = std::accumulate(declarations.begin(), declarations.end(), std::string(),
        [](std::string const& acc, auto const& element) {
            return !acc.empty() ? acc + " " + element.toString() : element.toString();
        });

    std::string returnCaluse;
    if (returns.size() == 1) {
        returnCaluse = returns.at(0);
    }
    else {
        std::string commaSeparatedReturns = std::accumulate(returns.begin(), returns.end(), std::string(),
            [](std::string const& acc, std::string const& element) {
                return !acc.empty() ? acc + ", " + element : element;
            });
        returnCaluse = std::format("<{}>", commaSeparatedReturns);
    }

    if (filters.empty()) {
        return std::format("{}\nSelect {}", declarationLine, returnCaluse);
    }

    std::string filterClause = std::accumulate(filters.begin(), filters.end(), std::string(),
        [](std::string const& acc, auto const& element) {
            return !acc.empty() ? acc + " " + element->toString() : element->toString();
        });
    return std::format("{}\nSelect {} {}", declarationLine, returnCaluse, filterClause);
}

std::vector<Declaration> SelectClause::getDeclarations() const {
    return this->declarations;
}

std::vector<std::string> SelectClause::getReturns() const {
    return this->returns;
}

std::vector<FilterClause*> SelectClause::getFilters() const {
    return this->filters;
}
