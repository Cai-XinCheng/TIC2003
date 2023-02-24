#pragma once

#include "AST/PQL/SelectClause.h"
#include <map>

// A class to transform PQL to SQL
class PQL2SQLTransformer {
public:
    static std::string transform(const SelectClause& selectClause);

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

    static std::map<std::string, TableInfo, std::less<>> declarationTableInfoMapping;

    static std::string transformDeclarations(const std::vector<Declaration>& declarations);

    static std::string transformResult(const std::vector<std::string>& result, const std::vector<Declaration>& declarations);

    static std::string transformFilters(const std::vector<FilterClause*>& filters);
};

