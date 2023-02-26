#include "stdafx.h"
#include "../source/Database.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace DatabaseTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestDatabase)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.

        // Test procedure
        // Grammer: stmtNo: [1-9][0-9]*, procedureName: LETTER(LETTER | DIGIT)*
        TEST_METHOD(CheckDatabaseProcedure)
        {
            // initialize the database and insert a procedure
            Database::initialize();
            Database::insertProcedure(1, "echo1");
            Database::insertProcedure(2, "echo2");
            Database::insertProcedure(4294967295, "a123bcd456");

            // retrieve the procedures from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, procedureName FROM procedures;");

            // create the test output string from the procedures retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,echo1$2,echo2$4294967295,a123bcd456$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test variable
        // Grammer: name: LETTER(LETTER | DIGIT)*, stmtNo: [1-9][0-9]*
        TEST_METHOD(CheckDatabaseVariable)
        {
            // initialize the database and insert a variable
            Database::initialize();
            Database::insertVariable("var1", 1);
            Database::insertVariable("var2", 1);
            Database::insertVariable("var2", 2);
            Database::insertVariable("v123var456", 4294967295);

            // retrieve the variables from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT name, stmtNo FROM variables;");

            // create the test output string from the variables retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "var1,1$var2,1$var2,2$v123var456,4294967295$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

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
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT value FROM constants;");

            // create the test output string from the constants retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "-9223372036854775808$10$12345$9223372036854775807$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test statement
        // Grammer: stmtNo: [1-9][0-9]*, type: read|print|assign|call|while|if
        TEST_METHOD(CheckDatabaseStatement)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertStatement(1, "read");
            Database::insertStatement(2, "read");
            Database::insertStatement(5, "print");
            Database::insertStatement(10, "assign");
            Database::insertStatement(20, "assign");
            Database::insertStatement(30, "call");
            Database::insertStatement(40, "while");
            Database::insertStatement(4294967295, "if");

            // retrieve the statements from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, type FROM statements;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,read$2,read$5,print$10,assign$20,assign$30,call$40,while$4294967295,if$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test assignment
        // Grammer: stmtNo: [1-9][0-9]*, variable: LETTER (LETTER | DIGIT)*, expression: expr '+' term | expr '-' term | term
        TEST_METHOD(CheckDatabaseAssignment)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertAssignment(1, "var1", "0");
            Database::insertAssignment(2, "var1", "x");
            Database::insertAssignment(10, "var2", "x + y * z");
            Database::insertAssignment(4294967295, "var3", "x - y / z % i");

            // retrieve the assignments from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, variable, expression FROM assignments;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,var1,0$2,var1,x$10,var2,x + y * z$4294967295,var3,x - y / z % i$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test next
        // Grammer: stmtNo: [1-9][0-9]*, nextStmtNo: [1-9][0-9]*
        TEST_METHOD(CheckDatabaseNext)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertNext(1, 2);
            Database::insertNext(1, 3);
            Database::insertNext(2, 5);
            Database::insertNext(4294967295, 100);

            // retrieve the nexts from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, nextStmtNo FROM nexts;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,2$1,3$2,5$4294967295,100$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test parent
        // Grammer: stmtNo: [1-9][0-9]*, parentStmtNo: [1-9][0-9]*
        TEST_METHOD(CheckDatabaseParent)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertParent(1, 2);
            Database::insertParent(2, 5);
            Database::insertParent(4294967295, 100);

            // retrieve the parents from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, parentStmtNo FROM parents;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,2$2,5$4294967295,100$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test call
        // Grammer: stmtNo: [1-9][0-9]*, calleeStmtNo: [1-9][0-9]*
        TEST_METHOD(CheckDatabaseCall)
        {
            // initialize the database and insert a statement
            Database::initialize();
            Database::insertCall(1, 2);
            Database::insertCall(2, 5);
            Database::insertCall(4294967295, 100);

            // retrieve the calls from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, calleeStmtNo FROM calls;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,2$2,5$4294967295,100$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Some private helper functions can be added below.
    private:
        static void generateTestOutput(const std::vector<std::string>& dbResults, std::string& testOutput) {
            for (std::string const& element : dbResults)
            {
                testOutput.append(element + "$");
            }
        }

        static void generateTestOutput(const std::vector<uint32_t>& dbResults, std::string& testOutput) {
            for (uint32_t const& element : dbResults)
            {
                testOutput.append(std::to_string(element) + "$");
            }
        }

        static void generateTestOutput(const std::vector<int64_t>& dbResults, std::string& testOutput) {
            for (int64_t const& element : dbResults)
            {
                testOutput.append(std::to_string(element) + "$");
            }
        }

        static void generateTestOutput(const std::vector<std::vector<std::string>>& dbResults, std::string& testOutput) {
            for (std::vector<std::string> const& row : dbResults)
            {
                for (size_t i = 0; i < row.size(); i++) {
                    if (i != 0) {
                        testOutput.append(",");
                    }
                    testOutput.append(row[i]);
                }
                testOutput.append("$");
            }
        }
    };
}
