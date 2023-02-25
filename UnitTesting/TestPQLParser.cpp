#include "stdafx.h"
#include "../source/Tokenizer.h"
#include "../source/PQLParser.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace PQLParserTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestPQLParser)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckParseQuery_ExampleQ1)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure p;";
            expectedOutput += "\n";
            expectedOutput += "Select p";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckParseQuery_ExampleQ2)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable v;";
            expectedOutput += "\n";
            expectedOutput += "Select v";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ3)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (6, s)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt s;";
            expectedOutput += "\n";
            expectedOutput += "Select s such that Next* (6, s)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ4)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Modifies (6, v)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable v;";
            expectedOutput += "\n";
            expectedOutput += "Select v such that Modifies (6, v)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ5)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Uses (14, v)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable v;";
            expectedOutput += "\n";
            expectedOutput += "Select v such that Uses (14, v)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ6)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += "Select a such that Parent* (w, a)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ7)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Parent (s, 7)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt s;";
            expectedOutput += "\n";
            expectedOutput += "Select s such that Parent (s, 7)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ8)
        {
            // create the input string
            std::string testInput = R"(
                variable v; procedure p;
                Select p such that Modifies (p, "x")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable v; procedure p;";
            expectedOutput += "\n";
            expectedOutput += R"(Select p such that Modifies (p, "x"))";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ9)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select p such that Calls (p, _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure p, q;";
            expectedOutput += "\n";
            expectedOutput += "Select p such that Calls (p, _)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ10)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p such that Calls* (p, "Third")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure p;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select p such that Calls* (p, "Third"))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ11)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select <p, q> such that Calls (p, q)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure p, q;";
            expectedOutput += "\n";
            expectedOutput += "Select <p, q> such that Calls (p, q)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ12)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("x", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a ("x", _))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ13)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a (_, _"count + 1"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a (_, _"count + 1"_))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ14_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a ("normSq", _"cenX * cenX"_))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ14_2)
        {
            // create the input string
            std::string testInput = R"(
                assign newa;
                Select newa pattern newa ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign newa;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select newa pattern newa ("normSq", _"cenX * cenX"_))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ15)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select w such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select w such that Parent* (w, a) pattern a ("count", _))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ16)
        {
            // create the input string
            std::string testInput = R"(
                assign a; variable v;
                Select a such that Uses (a, v) pattern a (v, _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; variable v;";
            expectedOutput += "\n";
            expectedOutput += "Select a such that Uses (a, v) pattern a (v, _)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ17_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Uses (a, "x")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a ("x", _) such that Uses (a, "x"))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ17_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Uses (a, "x") pattern a ("x", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a such that Uses (a, "x") pattern a ("x", _))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ18_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a such that Parent* (w, a) pattern a ("count", _))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ18_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("count", _) such that Parent* (w, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a ("count", _) such that Parent* (w, a))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ19)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (5, s) such that Next* (s, 12)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt s;";
            expectedOutput += "\n";
            expectedOutput += "Select s such that Next* (5, s) such that Next* (s, 12)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ20_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (1, a))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ20_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a; while w;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (1, a))!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ21)
        {
            // create the input string
            std::string testInput = R"(
                while w1, w2, w3;
                Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "while w1, w2, w3;";
            expectedOutput += "\n";
            expectedOutput += "Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckParseQuery_ExampleQ22)
        {
            // create the input string
            std::string testInput = R"(
                assign a1, a2; while w1, w2;
                Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign a1, a2; while w1, w2;";
            expectedOutput += "\n";
            expectedOutput += R"!(Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2))!";

            // Logger messages can be viewed in the Test Explorer
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        // Some private helper functions can be added below.
    private:
        // method to generate tokenized test output
        static void generateTestOutput(const std::string& input, std::string& testOutput)
        {
            // tokenize the query
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // parse the AST
            PQLParser parser;
            SelectClause selectClause = parser.parse(tokens);

            testOutput = selectClause.toString();
        }
    };
}
