#include "stdafx.h"
#include "../source/Database.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DatabaseTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestDatabase)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.

        // Test procedure
        // Grammer: LETTER(LETTER | DIGIT)*
        TEST_METHOD(CheckDatabaseProcedure)
        {
            // initialize the database and insert a procedure
            Database::initialize();
            Database::insertProcedure("echo1");
            Database::insertProcedure("echo2");
            Database::insertProcedure("a123bcd456");

            // retrieve the procedures from the database
            std::vector<std::string> dbResults;
            Database::getProcedures(dbResults);

            // create the test output string from the procedures retrieved
            std::string testOutput;
            for (unsigned int i = 0; i < dbResults.size(); i++)
            {
                testOutput.append(dbResults.at(i) + "$");
            }

            // create the expected output string
            std::string expectedOutput = "echo1$echo2$a123bcd456$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test variable
        // Grammer: LETTER(LETTER | DIGIT)*
        TEST_METHOD(CheckDatabaseVariable)
        {
            // initialize the database and insert a variable
            Database::initialize();
            Database::insertVariable("var1");
            Database::insertVariable("var2");
            Database::insertVariable("v123var456");

            // retrieve the variables from the database
            std::vector<std::string> dbResults;
            Database::getVariables(dbResults);

            // create the test output string from the variables retrieved
            std::string testOutput;
            for (unsigned int i = 0; i < dbResults.size(); i++)
            {
                testOutput.append(dbResults.at(i) + "$");
            }

            // create the expected output string
            std::string expectedOutput = "var1$var2$v123var456$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test constant
        // Grammer: sequences of digits (0-9)
        TEST_METHOD(CheckDatabaseConstant)
        {
            // initialize the database and insert a constant
            Database::initialize();
            Database::insertConstant(-9223372036854775807 - 1);
            Database::insertConstant(10);
            Database::insertConstant(12345);
            Database::insertConstant(9223372036854775807);

            // retrieve the constants from the database
            std::vector<int64_t> dbResults;
            Database::getConstants(dbResults);

            // create the test output string from the constants retrieved
            std::string testOutput;
            for (unsigned int i = 0; i < dbResults.size(); i++)
            {
                testOutput.append(std::to_string(dbResults.at(i)) + "$");
            }

            // create the expected output string
            std::string expectedOutput = "-9223372036854775808$10$12345$9223372036854775807$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test statement
        // Grammer: stmtNo: [1-9][0-9]*, type: read|print|assign
        TEST_METHOD(CheckDatabaseStatement)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertStatement(0, "read");
            Database::insertStatement(1, "read");
            Database::insertStatement(5, "print");
            Database::insertStatement(10, "assign");
            Database::insertStatement(4294967295, "assign");

            // retrieve the statements from the database
            std::vector<uint32_t> dbResults;
            Database::getStatements(dbResults);

            // create the test output string from the statements retrieved
            std::string testOutput;
            for (unsigned int i = 0; i < dbResults.size(); i++)
            {
                testOutput.append(std::to_string(dbResults.at(i)) + "$");
            }

            // create the expected output string
            std::string expectedOutput = "0$1$5$10$4294967295$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Some private helper functions can be added below.
    private:
    };
}
