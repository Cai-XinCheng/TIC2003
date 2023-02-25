#pragma once

#include "../ASTNode.h"
#include "Declaration.h"
#include "FilterClause.h"
#include <string>
#include <vector>

class SelectClause : public ASTNode {
public:
    static const std::string& nodeType;
    explicit SelectClause(const std::vector<Declaration>& declarations, const std::vector<std::string>& result, const std::vector<const FilterClause*>& filters);
    ~SelectClause() override;
    std::string toString() const override;
    std::vector<Declaration> getDeclarations() const;
    std::vector<std::string> getResult() const;
    std::vector<const FilterClause*> getFilters() const;

private:
    std::vector<Declaration> declarations;
    std::vector<std::string> result;
    std::vector<const FilterClause*> filters;
};
