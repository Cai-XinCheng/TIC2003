#pragma once

#include "PQL2SQLTransformer.h"
#include <map>
#include <numeric>
#include <format>

std::map<std::string, PQL2SQLTransformer::TableInfo, std::less<>> PQL2SQLTransformer::declarationTableInfoMapping({
        {"stmt", TableInfo("statements", "stmtNo")},
        {"read", TableInfo("(SELECT * FROM statements WHERE type = 'read')", "stmtNo")},
        {"print", TableInfo("(SELECT * FROM statements WHERE type = 'print')", "stmtNo")},
        {"call", TableInfo("(SELECT * FROM statements WHERE type = 'call')", "stmtNo")},
        {"while", TableInfo("whiles", "con_stmtNo")},
        {"if", TableInfo("ifs", "con_stmtNo")},
        {"assign", TableInfo("assignments", "stmtNo")},
        {"variable", TableInfo("variables", "name")},
        {"constant", TableInfo("constants", "value")},
        {"procedure", TableInfo("procedures", "procedureName")},
    });

std::string PQL2SQLTransformer::transform(const SelectClause& selectClause) {
    std::string sqlSelect = transformResult(selectClause.getResult(), selectClause.getDeclarations());
    std::string sqlFrom = transformDeclarations(selectClause.getDeclarations());
    std::string sqlWhere = transformFilters(selectClause.getFilters());

    return sqlWhere.empty()
        ? std::format("{} {}", sqlSelect, sqlFrom)
        : std::format("{} {} {}", sqlSelect, sqlFrom, sqlWhere);
}

std::string PQL2SQLTransformer::transformDeclarations(const std::vector<Declaration>& declarations) {
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

std::string PQL2SQLTransformer::transformResult(const std::vector<std::string>& result, const std::vector<Declaration>& declarations) {
    std::string commaSeparatedColumns = "";
    for (std::string const& element : result) {
        if (!commaSeparatedColumns.empty()) {
            commaSeparatedColumns += ", ";
        }

        std::string declarationDesignEntity;
        for (Declaration const& declaration : declarations) {
            std::vector<std::string> vec = declaration.getSynonyms();
            if (std::ranges::find(vec.begin(), vec.end(), element) != vec.end()) {
                declarationDesignEntity = declaration.getDesignEntity();
                break;
            }
        }
        TableInfo tableInfo = declarationTableInfoMapping.at(declarationDesignEntity);
        commaSeparatedColumns += std::format("{}.{}", element, tableInfo.getTableResultColumn());
    }
    return std::format("SELECT {}", commaSeparatedColumns);
}

std::string PQL2SQLTransformer::transformFilters(const std::vector<FilterClause*>& filters) {
    return "";
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
