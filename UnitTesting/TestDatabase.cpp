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
            // initialize the database and insert procedures
            Database::initialize();
            Database::insertProcedure("echo1");
            Database::insertProcedure("echo2");
            Database::insertProcedure("a123bcd456");

            // retrieve the procedures from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT procedureName FROM procedures;");

            // create the test output string from the procedures retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "echo1$echo2$a123bcd456$";

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
            // initialize the database and insert variables
            Database::initialize();
            Database::insertVariable("var1", 1, "use", "procedure1");
            Database::insertVariable("var2", 2, "use", "procedure1");
            Database::insertVariable("var2", 3, "modify", "procedure1");
            Database::insertVariable("v123var456", 4294967295, "modify", "pro123cedure");

            // retrieve the variables from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT name, stmtNo, relation, procedureName FROM variables;");

            // create the test output string from the variables retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "var1,1,use,procedure1$var2,2,use,procedure1$var2,3,modify,procedure1$v123var456,4294967295,modify,pro123cedure$";

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
            // initialize the database and insert constants
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
            // initialize the database and insert statements
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
            // initialize the database and insert assignments
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
            // initialize the database and insert nexts
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
            // initialize the database and insert parents
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
            // initialize the database and insert calls
            Database::initialize();
            Database::insertCall(1, "pro1", "pro2");
            Database::insertCall(2, "procedure", "pro");
            Database::insertCall(4294967295, "pro123cedure", "procedure123");

            // retrieve the calls from the database
            std::vector<std::vector<std::string>> dbResults;
            Database::select(dbResults, "SELECT stmtNo, callerName, calleeName FROM calls;");

            // create the test output string from the statements retrieved
            std::string testOutput;
            generateTestOutput(dbResults, testOutput);

            // create the expected output string
            std::string expectedOutput = "1,pro1,pro2$2,procedure,pro$4294967295,pro123cedure,procedure123$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the test output with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        // Test check_parent
        TEST_METHOD(CheckDatabaseFunction_check_parent)
        {
            // initialize the database and initialize a simplified version of Code5
            initializeSimplifiedCode5();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_parent(5 + 9, 7 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent(5 + 9, 8 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent(10 + 9, 11 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent(10 + 9, 13 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent(2 + 9, 3 + 9);", ""},
                {"SELECT 1 WHERE check_parent(4 + 9, 7 + 9);", ""},
                {"SELECT 1 WHERE check_parent(9 + 9, 5 + 9);", ""},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_parent_t
        TEST_METHOD(CheckDatabaseFunction_check_parent_t)
        {
            // initialize the database and initialize a simplified version of Code5
            initializeSimplifiedCode5();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_parent_t(5 + 9, 7 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent_t(10 + 9, 13 + 9);", "1$"},
                {"SELECT 1 WHERE check_parent_t(10 + 9, 14 + 9);", ""},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_next
        TEST_METHOD(CheckDatabaseFunction_check_next)
        {
            // initialize the database and initialize a simplified version of Code6
            initializeSimplifiedCode6();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_next(2 + 3, 3 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(3 + 3, 4 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(3 + 3, 7 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(5 + 3, 6 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(7 + 3, 9 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(8 + 3, 10 + 3);", "1$"},
                {"SELECT 1 WHERE check_next(6 + 3, 4 + 3);", ""},
                {"SELECT 1 WHERE check_next(7 + 3, 10 + 3);", ""},
                {"SELECT 1 WHERE check_next(8 + 3, 9 + 3);", ""},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_next_t
        TEST_METHOD(CheckDatabaseFunction_check_next_t)
        {
            // initialize the database and initialize a simplified version of Code6
            initializeSimplifiedCode6();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_next_t(1 + 3, 2 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(1 + 3, 3 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(2 + 3, 5 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(4 + 3, 3 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(5 + 3, 5 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(5 + 3, 8 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(5 + 3, 12 + 3);", "1$"},
                {"SELECT 1 WHERE check_next_t(8 + 3, 9 + 3);", ""},
                {"SELECT 1 WHERE check_next_t(5 + 3, 2 + 3);", ""},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_call
        TEST_METHOD(CheckDatabaseFunction_check_call)
        {
            // initialize the database and initialize a simplified version of Code6
            initializeSimplifiedCode6();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_call('First', 'Second');", "1$"},
                {"SELECT 1 WHERE check_call('Second', 'Third');", "1$"},
                {"SELECT 1 WHERE check_call('First', 'Third');", ""},
                {"SELECT 1 WHERE check_call('Second', 'First');", ""},
                {"SELECT 1 WHERE check_call('Second', NULL);", "1$"},
                {"SELECT 1 WHERE check_call('Third', NULL);", ""},
                {"SELECT 1 WHERE check_call(NULL, 'Third');", "1$"},
                {"SELECT 1 WHERE check_call(NULL, 'First');", ""},
                {"SELECT 1 WHERE check_call(NULL, NULL);", "1$"},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_call_t
        TEST_METHOD(CheckDatabaseFunction_check_call_t)
        {
            // initialize the database and initialize a simplified version of Code6
            initializeSimplifiedCode6();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_call_t('First', 'Second');", "1$"},
                {"SELECT 1 WHERE check_call_t('First', 'Third');", "1$"},
                {"SELECT 1 WHERE check_call_t('Second', 'First');", ""},
                {"SELECT 1 WHERE check_call_t('Second', NULL);", "1$"},
                {"SELECT 1 WHERE check_call_t('Third', NULL);", ""},
                {"SELECT 1 WHERE check_call_t(NULL, 'Third');", "1$"},
                {"SELECT 1 WHERE check_call_t(NULL, 'First');", ""},
                {"SELECT 1 WHERE check_call_t(NULL, NULL);", "1$"},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_modify
        TEST_METHOD(CheckDatabaseFunction_check_modify)
        {
            // initialize the database and initialize a simplified version of Code5
            initializeSimplifiedCode5();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_modify(1 + 9, 'count');", "1$"},
                {"SELECT 1 WHERE check_modify(7 + 9, 'cenX');", "1$"},
                {"SELECT 1 WHERE check_modify(9 + 9, 'x');", "1$"},
                {"SELECT 1 WHERE check_modify(10 + 9, 'flag');", "1$"},
                {"SELECT 1 WHERE check_modify(5 + 9, 'x');", "1$"},
                {"SELECT 1 WHERE check_modify('main', 'y');", "1$"},
                {"SELECT 1 WHERE check_modify('computeCentroid', 'flag');", "1$"},
                {"SELECT 1 WHERE check_modify(5 + 9, 'flag');", ""},
                {"SELECT 1 WHERE check_modify('printResults', 'normSq');", ""},
                {"SELECT 1 WHERE check_modify(1 + 9, NULL);", "1$"},
                {"SELECT 1 WHERE check_modify(4 + 9, NULL);", ""},
                {"SELECT 1 WHERE check_modify('computeCentroid', NULL);", "1$"},
                {"SELECT 1 WHERE check_modify('printResults', NULL);", ""},
            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Test check_use
        TEST_METHOD(CheckDatabaseFunction_check_use)
        {
            // initialize the database and initialize a simplified version of Code5
            initializeSimplifiedCode5();

            // query and expected outputs
            std::vector<std::vector<std::string>> selectAndExpectedOutputs = {
                {"SELECT 1 WHERE check_use(7 + 9, 'x');", "1$"},
                {"SELECT 1 WHERE check_use(10 + 9, 'count');", "1$"},
                {"SELECT 1 WHERE check_use(10 + 9, 'cenX');", "1$"},
                {"SELECT 1 WHERE check_use('main', 'cenX');", "1$"},
                {"SELECT 1 WHERE check_use('main', 'flag');", "1$"},
                {"SELECT 1 WHERE check_use('computeCentroid', 'x');", "1$"},
                {"SELECT 1 WHERE check_use(3 + 9, 'count');", ""},
                {"SELECT 1 WHERE check_use(10 + 9, 'flag');", ""},
                {"SELECT 1 WHERE check_use(9 + 9, 'y');", ""},
                {"SELECT 1 WHERE check_use('readPoint', 'x');", ""},
                {"SELECT 1 WHERE check_use(6 + 9, NULL);", "1$"},
                {"SELECT 1 WHERE check_use(2 + 9, NULL);", ""},
                {"SELECT 1 WHERE check_use('printResults', NULL);", "1$"},
                {"SELECT 1 WHERE check_use('readPoint', NULL);", ""},

            };

            // test cases
            testSelectCases(selectAndExpectedOutputs);
        }

        // Some private helper functions can be added below.
    private:
        static void initializeSimplifiedCode5() {
            int baseStmtNo = 0;
            Database::initialize();

            Database::insertVariable("flag", 1 + baseStmtNo, "modify", "main");
            Database::insertCall(2 + baseStmtNo, "main", "computeCentroid");
            Database::insertCall(3 + baseStmtNo, "main", "printResults");
            baseStmtNo += 3;

            Database::insertVariable("x", 1 + baseStmtNo, "modify", "readPoint");
            Database::insertVariable("y", 2 + baseStmtNo, "modify", "readPoint");
            baseStmtNo += 2;

            Database::insertVariable("flag", 1 + baseStmtNo, "use", "printResults");
            Database::insertVariable("cenX", 2 + baseStmtNo, "use", "printResults");
            Database::insertVariable("cenY", 3 + baseStmtNo, "use", "printResults");
            Database::insertVariable("normSq", 4 + baseStmtNo, "use", "printResults");
            baseStmtNo += 4;

            Database::insertVariable("count", 1 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenX", 2 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenY", 3 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("x", 5 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("y", 5 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("count", 6 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("count", 6 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("cenX", 7 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenX", 7 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("x", 7 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("cenY", 8 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenY", 8 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("y", 8 + baseStmtNo, "use", "computeCentroid");
            Database::insertCall(9 + baseStmtNo, "computeCentroid", "readPoint");
            Database::insertVariable("count", 10 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("flag", 11 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenX", 12 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenX", 12 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("count", 12 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("cenY", 13 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenY", 13 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("count", 13 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("normSq", 14 + baseStmtNo, "modify", "computeCentroid");
            Database::insertVariable("cenX", 14 + baseStmtNo, "use", "computeCentroid");
            Database::insertVariable("cenY", 14 + baseStmtNo, "use", "computeCentroid");

            Database::insertParent(6 + baseStmtNo, 5 + baseStmtNo);
            Database::insertParent(7 + baseStmtNo, 5 + baseStmtNo);
            Database::insertParent(8 + baseStmtNo, 5 + baseStmtNo);
            Database::insertParent(9 + baseStmtNo, 5 + baseStmtNo);
            Database::insertParent(11 + baseStmtNo, 10 + baseStmtNo);
            Database::insertParent(12 + baseStmtNo, 10 + baseStmtNo);
            Database::insertParent(13 + baseStmtNo, 10 + baseStmtNo);
        }

        static void initializeSimplifiedCode6() {
            int baseStmtNo = 0;
            Database::initialize();

            Database::insertCall(3 + baseStmtNo, "First", "Second");
            baseStmtNo += 3;

            Database::insertCall(5 + baseStmtNo, "Second", "Third");

            Database::insertNext(1 + baseStmtNo, 2 + baseStmtNo);
            Database::insertNext(2 + baseStmtNo, 3 + baseStmtNo);
            Database::insertNext(3 + baseStmtNo, 4 + baseStmtNo);
            Database::insertNext(3 + baseStmtNo, 7 + baseStmtNo);
            Database::insertNext(4 + baseStmtNo, 5 + baseStmtNo);
            Database::insertNext(5 + baseStmtNo, 6 + baseStmtNo);
            Database::insertNext(6 + baseStmtNo, 3 + baseStmtNo);
            Database::insertNext(7 + baseStmtNo, 8 + baseStmtNo);
            Database::insertNext(7 + baseStmtNo, 9 + baseStmtNo);
            Database::insertNext(8 + baseStmtNo, 10 + baseStmtNo);
            Database::insertNext(9 + baseStmtNo, 10 + baseStmtNo);
            Database::insertNext(10 + baseStmtNo, 11 + baseStmtNo);
            Database::insertNext(11 + baseStmtNo, 12 + baseStmtNo);
        }

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

        static void testSelectCases(const std::vector<std::vector<std::string>>& cases) {
            for (std::vector<std::string> const& item : cases) {
                // retrieve the results from the database
                std::vector<std::vector<std::string>> dbResults;
                Database::select(dbResults, item.at(0));

                // create the test output string from the statements retrieved
                std::string testOutput;
                generateTestOutput(dbResults, testOutput);

                // Logger messages can be viewed in the Test Explorer 
                // under "open additional output for this result" for each test case
                TestHelper::LogActualAndExpected(testOutput, item.at(1), false, item.at(0).c_str());

                // compare the test output with expected output
                Assert::IsTrue(testOutput == item.at(1));
            }
        }
    };
}
