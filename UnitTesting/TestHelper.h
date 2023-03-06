#pragma once

#include <string>

class TestHelper
{
public:
    static std::string reorderOutput(const std::string& original, const std::string& separator = ", ");

    static void LogActualAndExpected(
        const std::string& actual,
        const std::string& expected,
        const bool multilineMode = false,
        const char* section = nullptr
    );
};

