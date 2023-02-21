#pragma once

#include "../ASTNode.h"
#include <string>

class FilterClause : public ASTNode {
public:
    explicit FilterClause(const std::string& type);
};
