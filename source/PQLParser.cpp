#pragma once

#include "PQLParser.h"
#include "AST/PQL/SuchThatClause.h"
#include "AST/PQL/PatternClause.h"
#include "format"

SelectClause PQLParser::parse(std::vector<std::string>& tokens) {
    std::vector<Declaration> declarations;
    std::vector<std::string> returns;
    std::vector<FilterClause*> filters;

    unsigned int i = 0;
    while (i < tokens.size()) {
        std::string token = tokens.at(i);

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
            i++;

            std::string designEntity = token;
            std::vector<std::string> synonyms;

            while (i < tokens.size()) {
                token = tokens.at(i);
                if (token == ";") {
                    i++;
                    break;
                }
                synonyms.push_back(token);
                i++;
                if (i >= tokens.size() || !(tokens.at(i) == "," || tokens.at(i) == ";")) {
                    throw std::exception("QueryProcessor: invalid declaration");
                }
                if (tokens.at(i) == ",")
                {
                    i++;
                }
            }
            declarations.emplace_back(designEntity, synonyms);
        }
        else if (token == "Select") { // select
            i++;

            // result-cl
            if (i < tokens.size()) {
                token = tokens.at(i);
                if (token == "<") { // multiple returns
                    i++;

                    while (i < tokens.size())
                    {
                        token = tokens.at(i);
                        if (token == ">") {
                            i++;
                            break;
                        }
                        returns.push_back(token);
                        i++;
                        if (i >= tokens.size() || !(tokens.at(i) == "," || tokens.at(i) == ">")) {
                            throw std::exception("QueryProcessor: invalid returns");
                        }
                        if (tokens.at(i) == ",")
                        {
                            i++;
                        }
                    }
                }
                else { // single return
                    returns.push_back(token);
                    i++;
                }
            }

            // result-cl or pattern-cl
            while (i < tokens.size()) {
                token = tokens.at(i);
                if (token == "such") { // result-cl
                    if (i > tokens.size() - 8
                        || tokens.at(i + 1) != "that"
                        || tokens.at(i + 3) != "("
                        || tokens.at(i + 5) != ","
                        || tokens.at(i + 7) != ")") {
                        throw std::exception("QueryProcessor: invalid such clause");
                    }

                    std::string relationshipName = tokens.at(i + 2);
                    std::string relationshipArg1 = tokens.at(i + 4);
                    std::string relationshipArg2 = tokens.at(i + 6);
                    filters.push_back(new SuchThatClause(relationshipName, relationshipArg1, relationshipArg2));
                    i += 8;
                }
                else if (token == "pattern") { // pattern-cl
                    if (i > tokens.size() - 7 
                        || tokens.at(i + 2) != "("
                        || tokens.at(i + 4) != ","
                        || tokens.at(i + 6) != ")") {
                        throw std::exception("QueryProcessor: invalid pattern clause");
                    }

                    std::string synonymAssignment = tokens.at(i + 1);
                    std::string left = tokens.at(i + 3);
                    std::string right = tokens.at(i + 5);
                    filters.push_back(new PatternClause(synonymAssignment, left, right));
                    i += 7;
                }
                else {
                    throw std::exception(std::format(R"(QueryProcessor: unknown token "{}")", token).c_str());
                }
            }

        }
        else {
            throw std::exception(std::format(R"(QueryProcessor: unknown token "{}")", token).c_str());
        }
    }

    return SelectClause(declarations, returns, filters);
}
