#pragma once

#include "Factor.h"
#include <string>

class Term : public Factor {
public:
    explicit Term(const std::string& type);
};
