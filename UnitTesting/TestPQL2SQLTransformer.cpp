#include "stdafx.h"
#include "../source/Tokenizer.h"
#include "../source/PQLParser.h"
#include "../source/PQL2SQLTransformer.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace PQL2SQLTransformerTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestPQL2SQLTransformer)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckTransformQuery_ExampleQ1)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName";
            expectedOutput += " FROM procedures AS p";
            expectedOutput += "";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ2)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += "";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ3)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (6, s)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE is_next_transitive(6, s.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ4)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Modifies (6, v)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += " WHERE has_modify(6, v.name)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ5)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Uses (14, v)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += " WHERE has_use(14, v.name)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ6)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE is_parent_transitive(w.con_stmtNo, a.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ7)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Parent (s, 7)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE is_parent(s.stmtNo, 7)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ8)
        {
            // create the input string
            std::string testInput = R"(
                variable v; procedure p;
                Select p such that Modifies (p, "x")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName";
            expectedOutput += " FROM variables AS v, procedures AS p";
            expectedOutput += " WHERE has_modify(p.procedureName, 'x')";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ9)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select p such that Calls (p, _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName";
            expectedOutput += " FROM procedures AS p, procedures AS q";
            expectedOutput += " WHERE has_call(p.procedureName)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ10)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p such that Calls* (p, "Third")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName";
            expectedOutput += " FROM procedures AS p";
            expectedOutput += " WHERE has_call_transitive(p.procedureName, 'Third')";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ11)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select <p, q> such that Calls (p, q)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName, q.procedureName";
            expectedOutput += " FROM procedures AS p, procedures AS q";
            expectedOutput += " WHERE has_call(p.procedureName, q.procedureName)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ12)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("x", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.variable = 'x'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ13)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a (_, _"count + 1"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.expression LIKE '%count + 1%'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ14_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.variable = 'normSq' AND a.expression LIKE '%cenX * cenX%'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ14_2)
        {
            // create the input string
            std::string testInput = R"(
                assign newa;
                Select newa pattern newa ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT newa.stmtNo";
            expectedOutput += " FROM assignments AS newa";
            expectedOutput += " WHERE newa.variable = 'normSq' AND newa.expression LIKE '%cenX * cenX%'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ15)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select w such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT w.con_stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE is_parent_transitive(w.con_stmtNo, a.stmtNo) AND a.variable = 'count'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ16)
        {
            // create the input string
            std::string testInput = R"(
                assign a; variable v;
                Select a such that Uses (a, v) pattern a (v, _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, variables AS v";
            expectedOutput += " WHERE has_use(a.stmtNo, v.name) AND a.variable = v.name";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ17_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Uses (a, "x")
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE a.variable = 'x' AND has_use(a.stmtNo, 'x')";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ17_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Uses (a, "x") pattern a ("x", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE has_use(a.stmtNo, 'x') AND a.variable = 'x'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ18_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE is_parent_transitive(w.con_stmtNo, a.stmtNo) AND a.variable = 'count'";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ18_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("count", _) such that Parent* (w, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE a.variable = 'count' AND is_parent_transitive(w.con_stmtNo, a.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ19)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (5, s) such that Next* (s, 12)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE is_next_transitive(5, s.stmtNo) AND is_next_transitive(s.stmtNo, 12)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ20_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE a.variable = 'x' AND is_parent_transitive(w.con_stmtNo, a.stmtNo) AND is_next_transitive(1, a.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ20_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a.stmtNo";
            expectedOutput += " FROM assignments AS a, whiles AS w";
            expectedOutput += " WHERE has_modify(a.stmtNo, 'x') AND is_parent_transitive(w.con_stmtNo, a.stmtNo) AND is_next_transitive(1, a.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ21)
        {
            // create the input string
            std::string testInput = R"(
                while w1, w2, w3;
                Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT w1.con_stmtNo, w2.con_stmtNo, w3.con_stmtNo";
            expectedOutput += " FROM whiles AS w1, whiles AS w2, whiles AS w3";
            expectedOutput += " WHERE is_parent_transitive(w1.con_stmtNo, w2.con_stmtNo) AND is_parent_transitive(w2.con_stmtNo, w3.con_stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ22)
        {
            // create the input string
            std::string testInput = R"(
                assign a1, a2; while w1, w2;
                Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2)
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT a1.stmtNo";
            expectedOutput += " FROM assignments AS a1, assignments AS a2, whiles AS w1, whiles AS w2";
            expectedOutput += " WHERE a1.variable = 'x' AND a2.variable = 'x' AND a2.expression LIKE '%x%' AND is_next_transitive(a1.stmtNo, a2.stmtNo) AND is_parent_transitive(w2.con_stmtNo, a2.stmtNo) AND is_parent_transitive(w1.con_stmtNo, w2.con_stmtNo)";

            // Logger messages can be viewed in the Test Explorer
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        // Some private helper functions can be added below.
    private:
        // method to get tokenized test output
        static void getTestOutput(const std::string& input, std::string& testOutput)
        {
            // tokenize the query
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // parse the AST
            PQLParser parser;
            SelectClause selectClause = parser.parse(tokens);

            // transform the AST to SQL
            PQL2SQLTransformer transformer;
            testOutput = transformer.transform(selectClause);
        }
    };
}
