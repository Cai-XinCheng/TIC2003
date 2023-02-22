#pragma once

#include "PQLParser.h"
#include "AST/PQL/SuchThatClause.h"
#include "AST/PQL/PatternClause.h"

SelectClause PQLParser::parse(std::vector<std::string>& tokens) {
    std::vector<Declaration> declarations;
    std::vector<std::string> returns;
    std::vector<FilterClause> filters;

    unsigned int i = 0;
    while (i < tokens.size()) {
        std::string token = tokens.at(i);
        i++;

        if (token == "stmt"
            || token == "read"
            || token == "print"
            || token == "call"
            || token == "while"
            || token == "if"
            || token == "assign"
            || token == "variable"
            || token == "constant"
            || token == "procedure") { // declarations

            std::string designEntity = token;
            std::vector<std::string> synonyms;

            while (i < tokens.size()) {
                token = tokens.at(i);
                i++;
                if (token == ";") {
                    break;
                }
                synonyms.push_back(token);
            }
            declarations.emplace_back(designEntity, synonyms);
        }
        else if (token == "Select") { // select
            // result-cl
            if (i < tokens.size()) {
                token = tokens.at(i);
                i++;
                if (token == "<") { // multiple returns
                    while (i < tokens.size())
                    {
                        token = tokens.at(i);
                        i++;
                        if (token == ">") {
                            break;
                        }
                        returns.push_back(token);
                        if (i >= tokens.size() || tokens.at(i) != ",") {
                            throw std::exception((R"(QueryProcessor: expect ",", found ")" + tokens.at(i) + "\"").c_str());
                        }
                        i++;
                    }
                }
                else { // single return
                    returns.push_back(token);
                }
            }

            // result-cl or pattern-cl
            while (i < tokens.size()) {
                token = tokens.at(i);
                i++;
                if (token == "such") { // result-cl
                    if (i >= tokens.size() || tokens.at(i) != "that") {
                        throw std::exception(("QueryProcessor: expect such that, found such " + tokens.at(i)).c_str());
                    }
                    i++;

                    std::string relationshipName;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        relationshipName = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != "(") {
                        throw std::exception((R"(QueryProcessor: expect "(", found ")" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    std::string relationshipArg1;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        relationshipArg1 = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != ",") {
                        throw std::exception((R"(QueryProcessor: expect ",", found ")" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    std::string relationshipArg2;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        relationshipArg2 = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != ")") {
                        throw std::exception((R"!(QueryProcessor: expect ")", found ")!" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    filters.push_back(SuchThatClause(relationshipName, relationshipArg1, relationshipArg2));
                }
                else if (token == "pattern") { // pattern-cl
                    std::string synonymAssignment;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        synonymAssignment = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != "(") {
                        throw std::exception((R"(QueryProcessor: expect "(", found ")" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    std::string left;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        left = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != ",") {
                        throw std::exception((R"(QueryProcessor: expect ",", found ")" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    std::string right;
                    if (i < tokens.size()) {
                        token = tokens.at(i);
                        i++;
                        left = token;
                    }

                    if (i >= tokens.size() || tokens.at(i) != ")") {
                        throw std::exception((R"!(QueryProcessor: expect ")", found ")!" + tokens.at(i) + "\"").c_str());
                    }
                    i++;

                    filters.push_back(PatternClause(synonymAssignment, left, right));
                }
                else {
                    throw std::exception(("QueryProcessor: unknown token " + token).c_str());
                }
            }

        }
        else {
            throw std::exception(("QueryProcessor: unknown token " + token).c_str());
        }
    }

    return SelectClause(declarations, returns, filters);
}
