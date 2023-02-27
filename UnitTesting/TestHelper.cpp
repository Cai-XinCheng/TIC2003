#include "TestHelper.h"
#include "stdafx.h"

using Logger = Microsoft::VisualStudio::CppUnitTestFramework::Logger;

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

    Logger::WriteMessage("Test Output:");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }
    Logger::WriteMessage(actual.c_str());

    Logger::WriteMessage("\n");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }

    Logger::WriteMessage("Expected Output:");
    if (multilineMode) {
        Logger::WriteMessage("\n");
    }
    Logger::WriteMessage(expected.c_str());
    Logger::WriteMessage("\n");
}
