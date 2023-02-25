#pragma once

#include "AST/PQL/SelectClause.h"
#include "AST/PQL/SuchThatClause.h"
#include "AST/PQL/PatternClause.h"
#include <map>

// A class to transform PQL to SQL
class PQL2SQLTransformer {
public:
    std::string transform(const SelectClause& selectClause) const;

private:
    class TableInfo {
    public:
        TableInfo(const std::string& tableExpression, const std::string& tableResultColumn);
        std::string getTableExpression() const;
        std::string getTableResultColumn() const;
    private:
        std::string tableExpression;
        std::string tableResultColumn;
    };

    static const std::map<std::string, TableInfo, std::less<>> declarationTableInfoMapping;

    static const std::map<std::string, std::string, std::less<>> relationshipFunctionMapping;

    std::string transformDeclarations(const std::vector<Declaration>& declarations) const;

    std::string transformResult(const std::vector<std::string>& result, const std::vector<Declaration>& declarations) const;

    std::string transformFilters(const std::vector<const FilterClause*>& filters, const std::vector<Declaration>& declarations) const;

    std::string transformSuchThat(const SuchThatClause* suchThat, const std::vector<Declaration>& declarations) const;

    std::string transformPattern(const PatternClause* suchThat, const std::vector<Declaration>& declarations) const;

    std::string generateColumnRefBySynonym(const std::string& synonym, const std::vector<Declaration>& declarations) const;
};

