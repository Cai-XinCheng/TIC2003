#pragma once

#include "../ASTNode.h"
#include "FilterClause.h"
#include <string>
#include <vector>

class SelectClause : public ASTNode {
public:
    explicit SelectClause(const std::vector<std::string>& declarations, const std::vector<std::string>& returns, const std::vector<FilterClause>& filters);
    void getDeclarations(std::vector<std::string>& declarationsRef) const;
    void getReturns(std::vector<std::string>& returnsRef) const;
    void getFilters(std::vector<FilterClause>& filtersRef) const;

private:
    std::vector<std::string> declarations;
    std::vector<std::string> returns;
    std::vector<FilterClause> filters;
};
