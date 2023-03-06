#include "TestHelper.h"
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>

using Logger = Microsoft::VisualStudio::CppUnitTestFramework::Logger;

std::string TestHelper::reorderOutput(const std::string& original, const std::string& separator) {
    // split into vector
    std::vector<std::string> vec;
    size_t from = 0;
    size_t index;
    do {
        index = original.find(separator, from);

        if (index != std::string::npos) {
            vec.push_back(original.substr(from, index - from));
            from = index + 2;
            continue;
        }

        vec.push_back(original.substr(from));
        break;
    } while (true);

    // reorder
    std::ranges::sort(vec.begin(), vec.end());

    std::string output = "";
    for (size_t i = 0; i < vec.size(); i++) {
        if (i != 0) {
            output.append(separator);
        }
        output.append(vec[i]);
    }

    return output;
}

void TestHelper::LogActualAndExpected(
    const std::string& actual,
    const std::string& expected,
    const bool multilineMode,
    const char* section
) {
    // Logger messages can be viewed in the Test Explorer
    // under "open additional output for this result" for each test case
    if (section != nullptr) {
        Logger::WriteMessage("\n");
        Logger::WriteMessage(section);
        Logger::WriteMessage("\n");
    }

    Logger::WriteMessage("Test Output: ");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }
    Logger::WriteMessage(actual.c_str());

    Logger::WriteMessage("\n");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }

    Logger::WriteMessage("Expected Output: ");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }
    Logger::WriteMessage(expected.c_str());
    Logger::WriteMessage("\n");
}
