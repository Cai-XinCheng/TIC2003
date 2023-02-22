#pragma once

#include "AST/PQL/SelectClause.h"

// A class to parse tokens to the AST of PQL
class PQLParser {
public:
    SelectClause parse(std::vector<std::string>& tokens);
};

