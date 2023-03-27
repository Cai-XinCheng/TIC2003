#pragma once

#include "PQL2SQLTransformer.h"
#include "Tokenizer.h"
#include "ExpressionParser.h"
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
        {"Parent", "check_parent"},
        {"Parent*", "check_parent_t"},
        {"Next", "check_next"},
        {"Next*", "check_next_t"},
        {"Calls", "check_call"},
        {"Calls*", "check_call_t"},
        {"Modifies", "check_modify"},
        {"Uses", "check_use"},
    });

std::string PQL2SQLTransformer::transform(const SelectClause& selectClause) const {
    std::vector<Declaration> declarations = selectClause.getDeclarations();
    std::vector<StatefulDeclaration> statefulDeclarations;
    for (auto const& declaration : declarations) {
        statefulDeclarations.emplace_back(declaration);
    }

    std::string sqlSelect = transformResult(selectClause.getResult(), statefulDeclarations);
    std::string sqlWhere = transformFilters(selectClause.getFilters(), statefulDeclarations);
    std::string sqlFrom = transformDeclarations(statefulDeclarations);

    return sqlWhere.empty()
        ? std::format("{} {}", sqlSelect, sqlFrom)
        : std::format("{} {} {}", sqlSelect, sqlFrom, sqlWhere);
}

std::string PQL2SQLTransformer::transformDeclarations(const std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string commaSeparatedTables = "";
    for (StatefulDeclaration const& statefulDeclaration : statefulDeclarations) {
        Declaration declaration = statefulDeclaration.getDeclaration();
        TableInfo tableInfo = declarationTableInfoMapping.at(declaration.getDesignEntity());
        for (std::string const& synonym : declaration.getSynonyms()) {
            if (!statefulDeclaration.isUsed(synonym)) {
                continue;
            }
            if (!commaSeparatedTables.empty()) {
                commaSeparatedTables += ", ";
            }
            commaSeparatedTables += std::format("{} AS {}", tableInfo.getTableExpression(), synonym);
        }
    }
    return std::format("FROM {}", commaSeparatedTables);
}

std::string PQL2SQLTransformer::transformResult(const std::vector<std::string>& result, std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string commaSeparatedColumns = "";
    for (std::string const& element : result) {
        if (!commaSeparatedColumns.empty()) {
            commaSeparatedColumns += ", ";
        }

        commaSeparatedColumns += generateColumnRefBySynonym(element, statefulDeclarations);
    }
    return std::format("SELECT DISTINCT {}", commaSeparatedColumns);
}

std::string PQL2SQLTransformer::transformFilters(const std::vector<const FilterClause*>& filters, std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string andSeparatedFilters = "";
    for (const FilterClause* filter : filters) {
        if (!andSeparatedFilters.empty()) {
            andSeparatedFilters += " AND ";
        }

        std::string filterType = filter->getType();
        if (filterType == SuchThatClause::nodeType) {
            const auto* suchThat = dynamic_cast<const SuchThatClause*>(filter);
            andSeparatedFilters += transformSuchThat(suchThat, statefulDeclarations);
        }
        else if (filterType == PatternClause::nodeType) {
            const auto* pattern = dynamic_cast<const PatternClause*>(filter);
            andSeparatedFilters += transformPattern(pattern, statefulDeclarations);
        }
        else {
            throw std::invalid_argument("PQL2SQLTransformer: unknown filter type");
        }
    }
    return !andSeparatedFilters.empty()
        ? std::format("WHERE {}", andSeparatedFilters)
        : "";
}

std::string PQL2SQLTransformer::transformSuchThat(const SuchThatClause* suchThat, std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string relationshipName = suchThat->getRelationshipName();
    std::string functionName = relationshipFunctionMapping.at(relationshipName);
    std::string arg1 = suchThat->getRelationshipArg1();
    std::string arg2 = suchThat->getRelationshipArg2();

    auto transformArg = [&](const std::string& arg) -> std::string {
        if (arg == "_") {
            return "NULL";
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
            return generateColumnRefBySynonym(arg, statefulDeclarations);
        }
    };

    std::string transformedArg1 = transformArg(arg1);
    std::string transformedArg2 = transformArg(arg2);

    return std::format("{}({}, {})", functionName, transformedArg1, transformedArg2);
}

std::string PQL2SQLTransformer::transformPattern(const PatternClause* pattern, std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string synonymAssignment = pattern->getSynonymAssignment();
    generateColumnRefBySynonym(synonymAssignment, statefulDeclarations);

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
        std::string columnRef = generateColumnRefBySynonym(left, statefulDeclarations);
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
        bool hasPlaceholder = false;

        if (temp.at(0) == '_') {
            hasPlaceholder = true;
            beginningWildcard = "%";
            temp = temp.substr(1);
        }
        if (temp.at(temp.length() - 1) == '_') {
            hasPlaceholder = true;
            endWildcard = "%";
            temp = temp.substr(0, temp.length() - 1);
        }

        std::string stringContent = temp.substr(1, temp.length() - 2);

        // tokenize the expression
        Tokenizer tk;
        std::vector<std::string> tokens;
        tk.tokenize(stringContent, tokens);

        // parse the AST
        ExpressionParser parser;
        const ExpressionNode* expressionNode = parser.parse(tokens);

        // normalized expression
        std::string normalizedStringContent;
        try {
            normalizedStringContent = expressionNode->toString();
        }
        catch (...) {
            delete expressionNode;
            throw;
        }
        delete expressionNode;

        transformedRight = !hasPlaceholder
            ? std::format("{}.expression = '{}'", synonymAssignment, normalizedStringContent)
            : std::format("{}.expression LIKE '{}{}{}'", synonymAssignment, beginningWildcard, normalizedStringContent, endWildcard);
    }

    return !transformedLeft.empty() && !transformedRight.empty()
        ? std::format("{} AND {}", transformedLeft, transformedRight)
        : transformedLeft + transformedRight;
}

std::string PQL2SQLTransformer::generateColumnRefBySynonym(const std::string& synonym, std::vector<StatefulDeclaration>& statefulDeclarations) const {
    std::string declarationDesignEntity;
    for (StatefulDeclaration& statefulDeclaration : statefulDeclarations) {
        Declaration declaration = statefulDeclaration.getDeclaration();
        std::vector<std::string> vec = declaration.getSynonyms();
        if (std::ranges::find(vec.begin(), vec.end(), synonym) != vec.end()) {
            declarationDesignEntity = declaration.getDesignEntity();
            statefulDeclaration.markAsUsed(synonym);
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

PQL2SQLTransformer::StatefulDeclaration::StatefulDeclaration(const Declaration& declaration)
    : declaration(declaration) {
}

Declaration PQL2SQLTransformer::StatefulDeclaration::getDeclaration() const {
    return declaration;
}

bool PQL2SQLTransformer::StatefulDeclaration::isUsed(const std::string& synonym) const {
    return usedSynonyms.contains(synonym);
}

void PQL2SQLTransformer::StatefulDeclaration::markAsUsed(const std::string& synonym) {
    usedSynonyms.insert(synonym);
}
