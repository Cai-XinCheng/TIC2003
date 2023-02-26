#pragma once

#include "PQL2SQLTransformer.h"
#include <map>
#include <numeric>
#include <format>

const std::map<std::string, PQL2SQLTransformer::TableInfo, std::less<>> PQL2SQLTransformer::declarationTableInfoMapping({
        {"stmt", TableInfo("statements", "stmtNo")},
        {"read", TableInfo("(SELECT * FROM statements WHERE type = 'read')", "stmtNo")},
        {"print", TableInfo("(SELECT * FROM statements WHERE type = 'print')", "stmtNo")},
        {"call", TableInfo("(SELECT * FROM statements WHERE type = 'call')", "stmtNo")},
        {"while", TableInfo("(SELECT * FROM statements WHERE type = 'while')", "stmtNo")},
        {"if", TableInfo("(SELECT * FROM statements WHERE type = 'if')", "stmtNo")},
        {"assign", TableInfo("assignments", "stmtNo")},
        {"variable", TableInfo("variables", "name")},
        {"constant", TableInfo("constants", "value")},
        {"procedure", TableInfo("procedures", "procedureName")},
    });

const std::map<std::string, std::string, std::less<>> PQL2SQLTransformer::relationshipFunctionMapping({
        {"Parent", "is_parent"},
        {"Parent*", "is_parent_t"},
        {"Next", "is_next"},
        {"Next*", "is_next_t"},
        {"Calls", "has_call"},
        {"Calls*", "has_call_t"},
        {"Modifies", "has_modify"},
        {"Uses", "has_use"},
    });

std::string PQL2SQLTransformer::transform(const SelectClause& selectClause) const {
    std::string sqlSelect = transformResult(selectClause.getResult(), selectClause.getDeclarations());
    std::string sqlFrom = transformDeclarations(selectClause.getDeclarations());
    std::string sqlWhere = transformFilters(selectClause.getFilters(), selectClause.getDeclarations());

    return sqlWhere.empty()
        ? std::format("{} {}", sqlSelect, sqlFrom)
        : std::format("{} {} {}", sqlSelect, sqlFrom, sqlWhere);
}

std::string PQL2SQLTransformer::transformDeclarations(const std::vector<Declaration>& declarations) const {
    std::string commaSeparatedTables = "";
    for (Declaration const& declaration : declarations) {
        TableInfo tableInfo = declarationTableInfoMapping.at(declaration.getDesignEntity());
        for (std::string const& synonym : declaration.getSynonyms()) {
            if (!commaSeparatedTables.empty()) {
                commaSeparatedTables += ", ";
            }
            commaSeparatedTables += std::format("{} AS {}", tableInfo.getTableExpression(), synonym);
        }
    }
    return std::format("FROM {}", commaSeparatedTables);
}

std::string PQL2SQLTransformer::transformResult(const std::vector<std::string>& result, const std::vector<Declaration>& declarations) const {
    std::string commaSeparatedColumns = "";
    for (std::string const& element : result) {
        if (!commaSeparatedColumns.empty()) {
            commaSeparatedColumns += ", ";
        }

        commaSeparatedColumns += generateColumnRefBySynonym(element, declarations);
    }
    return std::format("SELECT {}", commaSeparatedColumns);
}

std::string PQL2SQLTransformer::transformFilters(const std::vector<const FilterClause*>& filters, const std::vector<Declaration>& declarations) const {
    std::string andSeparatedFilters = "";
    for (const FilterClause* filter : filters) {
        if (!andSeparatedFilters.empty()) {
            andSeparatedFilters += " AND ";
        }

        std::string filterType = filter->getType();
        if (filterType == SuchThatClause::nodeType) {
            const auto* suchThat = dynamic_cast<const SuchThatClause*>(filter);
            andSeparatedFilters += transformSuchThat(suchThat, declarations);
        }
        else if (filterType == PatternClause::nodeType) {
            const auto* pattern = dynamic_cast<const PatternClause*>(filter);
            andSeparatedFilters += transformPattern(pattern, declarations);
        }
        else {
            throw std::invalid_argument("PQL2SQLTransformer: unknown filter type");
        }
    }
    return !andSeparatedFilters.empty()
        ? std::format("WHERE {}", andSeparatedFilters)
        : "";
}

std::string PQL2SQLTransformer::transformSuchThat(const SuchThatClause* suchThat, const std::vector<Declaration>& declarations) const {
    std::string relationshipName = suchThat->getRelationshipName();
    std::string functionName = relationshipFunctionMapping.at(relationshipName);
    std::string arg1 = suchThat->getRelationshipArg1();
    std::string arg2 = suchThat->getRelationshipArg2();

    auto transformArg = [&](const std::string& arg) -> std::string {
        if (arg == "_") {
            return "";
        }

        char firstChar = arg.at(0);
        if (isdigit(firstChar)) {
            // nubmer
            return arg;
        }
        else if (firstChar == '"') {
            // string
            std::string stringContent = arg.substr(1, arg.length() - 2);
            return std::format("'{}'", stringContent);
        }
        else {
            // synonym
            return generateColumnRefBySynonym(arg, declarations);
        }
    };

    std::string transformedArg1 = transformArg(arg1);
    std::string transformedArg2 = transformArg(arg2);

    return !transformedArg2.empty()
        ? std::format("{}({}, {})", functionName, transformedArg1, transformedArg2)
        : std::format("{}({})", functionName, transformedArg1);
}

std::string PQL2SQLTransformer::transformPattern(const PatternClause* pattern, const std::vector<Declaration>& declarations) const {
    std::string synonymAssignment = pattern->getSynonymAssignment();

    // left
    std::string left = pattern->getLeft();
    std::string transformedLeft;
    if (left == "_") {
        // entRef is _
        transformedLeft = "";
    }
    else if (left.at(0) == '"') {
        // entRef is string
        std::string stringContent = left.substr(1, left.length() - 2);
        transformedLeft = std::format("{}.variable = '{}'", synonymAssignment, stringContent);
    }
    else {
        // synonym
        std::string columnRef = generateColumnRefBySynonym(left, declarations);
        transformedLeft = std::format("{}.variable = {}", synonymAssignment, columnRef);
    }

    // right
    std::string right = pattern->getRight();
    std::string transformedRight;
    if (right == "_") {
        // expression-spec is _
        transformedRight = "";
    }
    else {
        std::string temp = right;
        std::string beginningWildcard;
        std::string endWildcard;

        if (temp.at(0) == '_') {
            beginningWildcard = "%";
            temp = temp.substr(1);
        }
        if (temp.at(temp.length() - 1) == '_') {
            endWildcard = "%";
            temp = temp.substr(0, temp.length() - 1);
        }

        std::string stringContent = temp.substr(1, temp.length() - 2);
        transformedRight = std::format("{}.expression LIKE '{}{}{}'", synonymAssignment, beginningWildcard, stringContent, endWildcard);
    }

    return !transformedLeft.empty() && !transformedRight.empty()
        ? std::format("{} AND {}", transformedLeft, transformedRight)
        : transformedLeft + transformedRight;
}

std::string PQL2SQLTransformer::generateColumnRefBySynonym(const std::string& synonym, const std::vector<Declaration>& declarations) const {
    std::string declarationDesignEntity;
    for (Declaration const& declaration : declarations) {
        std::vector<std::string> vec = declaration.getSynonyms();
        if (std::ranges::find(vec.begin(), vec.end(), synonym) != vec.end()) {
            declarationDesignEntity = declaration.getDesignEntity();
            break;
        }
    }
    TableInfo tableInfo = declarationTableInfoMapping.at(declarationDesignEntity);
    return std::format("{}.{}", synonym, tableInfo.getTableResultColumn());
}

PQL2SQLTransformer::TableInfo::TableInfo(const std::string& tableExpression, const std::string& tableResultColumn)
    : tableExpression(tableExpression), tableResultColumn(tableResultColumn) {
}

std::string PQL2SQLTransformer::TableInfo::getTableExpression() const {
    return this->tableExpression;
}

std::string PQL2SQLTransformer::TableInfo::getTableResultColumn() const {
    return this->tableResultColumn;
}
