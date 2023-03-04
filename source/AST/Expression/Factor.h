#pragma once

#include "ExpressionNode.h"
#include <string>

class Factor : public ExpressionNode {
public:
    explicit Factor(const std::string& type);
};
