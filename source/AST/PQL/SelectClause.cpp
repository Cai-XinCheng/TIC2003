#pragma once

#include "SelectClause.h"
#include <format>
#include <numeric>

SelectClause::SelectClause(const std::vector<Declaration>& declarations, const std::vector<std::string>& result, const std::vector<FilterClause*>& filters)
    : ASTNode("SelectClause"), declarations(declarations), result(result), filters(filters) {
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

    std::string resultCaluse;
    if (result.size() == 1) {
        resultCaluse = result.at(0);
    }
    else {
        std::string commaSeparatedResult = std::accumulate(result.begin(), result.end(), std::string(),
            [](std::string const& acc, std::string const& element) {
                return !acc.empty() ? acc + ", " + element : element;
            });
        resultCaluse = std::format("<{}>", commaSeparatedResult);
    }

    if (filters.empty()) {
        return std::format("{}\nSelect {}", declarationLine, resultCaluse);
    }

    std::string filterClause = std::accumulate(filters.begin(), filters.end(), std::string(),
        [](std::string const& acc, auto const& element) {
            return !acc.empty() ? acc + " " + element->toString() : element->toString();
        });
    return std::format("{}\nSelect {} {}", declarationLine, resultCaluse, filterClause);
}

std::vector<Declaration> SelectClause::getDeclarations() const {
    return this->declarations;
}

std::vector<std::string> SelectClause::getResult() const {
    return this->result;
}

std::vector<FilterClause*> SelectClause::getFilters() const {
    return this->filters;
}
