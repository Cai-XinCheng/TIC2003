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
        TEST_METHOD(CheckTransformQuery_ExampleQ01)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT p.procedureName";
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

        TEST_METHOD(CheckTransformQuery_ExampleQ02)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += "";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ03)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (6, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE check_next_t(6, s.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ04)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Modifies (6, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += " WHERE check_modify(6, v.name)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ05)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Uses (14, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += " WHERE check_use(14, v.name)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ06)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE check_parent_t(w.stmtNo, a.stmtNo)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ07)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Parent (s, 7)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE check_parent(s.stmtNo, 7)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ08)
        {
            // create the input string
            std::string testInput = R"(
                variable v; procedure p;
                Select p such that Modifies (p, "x")
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT p.procedureName";
            expectedOutput += " FROM procedures AS p";
            expectedOutput += " WHERE check_modify(p.procedureName, 'x')";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ09)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select p such that Calls (p, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT p.procedureName";
            expectedOutput += " FROM procedures AS p";
            expectedOutput += " WHERE check_call(p.procedureName, NULL)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_ExampleQ010)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p such that Calls* (p, "Third")
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT p.procedureName";
            expectedOutput += " FROM procedures AS p";
            expectedOutput += " WHERE check_call_t(p.procedureName, 'Third')";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT p.procedureName, q.procedureName";
            expectedOutput += " FROM procedures AS p, procedures AS q";
            expectedOutput += " WHERE check_call(p.procedureName, q.procedureName)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.expression LIKE '%((count) + (1))%'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.variable = 'normSq' AND a.expression LIKE '%((cenX) * (cenX))%'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT newa.stmtNo";
            expectedOutput += " FROM assignments AS newa";
            expectedOutput += " WHERE newa.variable = 'normSq' AND newa.expression LIKE '%((cenX) * (cenX))%'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT w.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE check_parent_t(w.stmtNo, a.stmtNo) AND a.variable = 'count'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, variables AS v";
            expectedOutput += " WHERE check_use(a.stmtNo, v.name) AND a.variable = v.name";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE a.variable = 'x' AND check_use(a.stmtNo, 'x')";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a";
            expectedOutput += " WHERE check_use(a.stmtNo, 'x') AND a.variable = 'x'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE check_parent_t(w.stmtNo, a.stmtNo) AND a.variable = 'count'";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE a.variable = 'count' AND check_parent_t(w.stmtNo, a.stmtNo)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT s.stmtNo";
            expectedOutput += " FROM statements AS s";
            expectedOutput += " WHERE check_next_t(5, s.stmtNo) AND check_next_t(s.stmtNo, 12)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE a.variable = 'x' AND check_parent_t(w.stmtNo, a.stmtNo) AND check_next_t(1, a.stmtNo)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a.stmtNo";
            expectedOutput += " FROM assignments AS a, (SELECT * FROM statements WHERE type = 'while') AS w";
            expectedOutput += " WHERE check_modify(a.stmtNo, 'x') AND check_parent_t(w.stmtNo, a.stmtNo) AND check_next_t(1, a.stmtNo)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT w1.stmtNo, w2.stmtNo, w3.stmtNo";
            expectedOutput += " FROM (SELECT * FROM statements WHERE type = 'while') AS w1, (SELECT * FROM statements WHERE type = 'while') AS w2, (SELECT * FROM statements WHERE type = 'while') AS w3";
            expectedOutput += " WHERE check_parent_t(w1.stmtNo, w2.stmtNo) AND check_parent_t(w2.stmtNo, w3.stmtNo)";

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

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT a1.stmtNo";
            expectedOutput += " FROM assignments AS a1, assignments AS a2, (SELECT * FROM statements WHERE type = 'while') AS w1, (SELECT * FROM statements WHERE type = 'while') AS w2";
            expectedOutput += " WHERE a1.variable = 'x' AND a2.variable = 'x' AND a2.expression LIKE '%(x)%' AND check_next_t(a1.stmtNo, a2.stmtNo) AND check_parent_t(w2.stmtNo, a2.stmtNo) AND check_parent_t(w1.stmtNo, w2.stmtNo)";

            // Logger messages can be viewed in the Test Explorer
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTransformQuery_Performance1)
        {
            // create the input string
            std::string testInput = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select v pattern a(v,"y + 1")
            )";

            // create the test output string from the query
            std::string testOutput;
            getTestOutput(testInput, testOutput);


            // create the expected output string
            std::string expectedOutput = "SELECT DISTINCT v.name";
            expectedOutput += " FROM assignments AS a, variables AS v";
            expectedOutput += " WHERE a.variable = v.name AND a.expression LIKE '((y) + (1))'";

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
