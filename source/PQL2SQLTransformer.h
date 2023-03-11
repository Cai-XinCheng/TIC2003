#pragma once

#include "AST/PQL/SelectClause.h"
#include "AST/PQL/SuchThatClause.h"
#include "AST/PQL/PatternClause.h"
#include <map>
#include <set>

// A class to transform PQL to SQL
class PQL2SQLTransformer {
public:
    std::string transform(const SelectClause& selectClause) const;

private:
    class TableInfo {
    public:
        explicit TableInfo(const std::string& tableExpression, const std::string& tableResultColumn);
        std::string getTableExpression() const;
        std::string getTableResultColumn() const;
    private:
        std::string tableExpression;
        std::string tableResultColumn;
    };
    class StatefulDeclaration {
    public:
        explicit StatefulDeclaration(const Declaration& declaration);
        Declaration getDeclaration() const;
        bool isUsed(const std::string& synonym) const;
        void markAsUsed(const std::string& synonym);
    private:
        Declaration declaration;
        std::set<std::string, std::less<>> usedSynonyms;
    };

    static const std::map<std::string, TableInfo, std::less<>> declarationTableInfoMapping;

    static const std::map<std::string, std::string, std::less<>> relationshipFunctionMapping;

    std::string transformDeclarations(const std::vector<StatefulDeclaration>& statefulDeclarations) const;

    std::string transformResult(const std::vector<std::string>& result, std::vector<StatefulDeclaration>& statefulDeclarations) const;

    std::string transformFilters(const std::vector<const FilterClause*>& filters, std::vector<StatefulDeclaration>& statefulDeclarations) const;

    std::string transformSuchThat(const SuchThatClause* suchThat, std::vector<StatefulDeclaration>& statefulDeclarations) const;

    std::string transformPattern(const PatternClause* suchThat, std::vector<StatefulDeclaration>& statefulDeclarations) const;

    std::string generateColumnRefBySynonym(const std::string& synonym, std::vector<StatefulDeclaration>& statefulDeclarations) const;
};

