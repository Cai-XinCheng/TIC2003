#pragma once

#include "Term.h"
#include <string>

class Expression : public Term {
public:
    explicit Expression(const std::string& type);
};
