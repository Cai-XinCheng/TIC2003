#include "stdafx.h"
#include "../source/SourceProcessor.h"
#include "../source/QueryProcessor.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace SPATests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestSPA)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckSPA_ExampleQ01) 
        {
            initializeCode5();

            std::string query = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string
            std::string expectedOutput = TestHelper::reorderOutput("main, readPoint, printResults, computeCentroid");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
 
            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckSPA_ExampleQ02)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                variable v;
                Select v
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string
            std::string expectedOutput = TestHelper::reorderOutput("flag, count, cenX, cenY, x, y, normSq");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ03)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Next* (15, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14, 15, 16, 17, 18, 19, 20, 21, 22, 23");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ04)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies (15, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("count");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ05)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Uses (23, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("cenX, cenY");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ06)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a such that Parent* (w, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("15, 16, 17");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ07)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent (s, 16)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ08)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                variable v; procedure p;
                Select p such that Modifies (p, "x")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("main, computeCentroid, readPoint");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ09)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                procedure p, q;
                Select p such that Calls (p, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("First, Second");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ010)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Calls* (p, "Third")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("First, Second");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ11)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                procedure p, q;
                Select <p, q> such that Calls (p, q)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("First Second, Second Third");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ12)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a ("cenX", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("11, 16, 21");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ13)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"count + 1"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("15");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ14_1)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("23");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ14_2)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign newa;
                Select newa pattern newa ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("23");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ15)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select w such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ16)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select a such that Uses (a, v) pattern a (v, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("15, 16, 17, 21, 22");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ17_1)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Uses (a, "x")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ17_2)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a such that Uses (a, "x") pattern a ("x", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ18_1)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("15");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ18_2)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a pattern a ("count", _) such that Parent* (w, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("15");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ19)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Next* (8, s) such that Next* (s, 15)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("6, 7, 8, 9, 10, 11, 12, 13, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ20_1)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (4, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ20_2)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (4, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ21_Code5)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                while w1, w2, w3;
                Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ21_Code6)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                while w1, w2, w3;
                Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ22_Code5)
        {
            initializeCode5();

            // create the input string
            std::string query = R"(
                assign a1, a2; while w1, w2;
                Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_ExampleQ22_Code6)
        {
            initializeCode6();

            // create the input string
            std::string query = R"(
                assign a1, a2; while w1, w2;
                Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query01)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent (s, 10)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query02)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent (r, 18)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query03)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Parent* (i, 13)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("9, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query04)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                while w; call c;
                Select w such that Parent* (w, c)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query05)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Parent* (s, a) pattern a ("a",_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 7, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query06)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1, read");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query07)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies (8, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("var1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query08)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Modifies (w, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query09)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "g")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1, read");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query10)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Uses (i, "b")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("9, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query11)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i such that Uses (i, "c") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("7, 9, 13");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query12)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p pattern a (v, _"c"_) such that Uses (p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1, print");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query13)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p such that Uses (p, v) pattern a (v, _"var1"_) 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1, print");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query14)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Modifies(s, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 17");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query15)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies(p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1, read");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query16)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i pattern a (_,_"var1"_) such that Modifies (i, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query17)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query18)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query19)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                procedure p; assign a;
                Select p such that Uses(p, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("p1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query20)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses (s, "a") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 7, 9, 10, 11, 14, 22");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query21)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses(s, "a") such that Modifies (s, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 7, 9, 10");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query22)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s; if i;
                Select s such that Uses(s, "a") such that Modifies (s, "a") such that Parent* (i, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("9, 10");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query23)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Next(2, s) pattern a (_,_"c + b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query24)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select a such that Next*(1, a) pattern a (_,_"b + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query25)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query26)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_, _"3 + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query27)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent* (5, s) such that Modifies (s, "var3")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query28)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Uses (a, "c") pattern a (_,_"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query29)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select a such that Uses(i, "var1") such that Parent* (i, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query30)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, a) pattern a ("sum",_"var4"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query31)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, "var1") such that Next*(1, a) pattern a ("sum",_"var1*var2"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query32)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next(i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query33)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next* (i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query34)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                stmt s; assign b;
                Select b such that Next*(1, b) such that Uses (b, "c") pattern b (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query35)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"a+b"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple1_Query36)
        {
            initializeSimple1();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"b*c"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query01)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent (s, 10)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query02)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent (r, 18)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query03)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Parent* (i, 13)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query04)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                while w; call c;
                Select w such that Parent* (w, c)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query05)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Parent* (s, a) pattern a ("a",_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query06)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("modify, read, print");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query07)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies (8, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c, d");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query08)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Modifies (w, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query09)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "g")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query10)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Uses (i, "b")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query11)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i such that Uses (i, "c") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query12)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p pattern a (v, _"c"_) such that Uses (p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("modify, print");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query13)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p such that Uses (p, v) pattern a (v, _"var1"_) 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("modify");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query14)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Modifies(s, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 3, 5, 6, 8, 9, 12, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query15)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies(p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("modify, read, print");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query16)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i pattern a (_,_"var1"_) such that Modifies (i, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query17)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("2, 3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query18)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query19)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                procedure p; assign a;
                Select p such that Uses(p, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("modify");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query20)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses (s, "a") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("2, 5, 6, 8, 9, 15");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query21)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses(s, "a") such that Modifies (s, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("2, 5, 6, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query22)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s; if i;
                Select s such that Uses(s, "a") such that Modifies (s, "a") such that Parent* (i, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query23)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Next(2, s) pattern a (_,_"c + b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query24)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select a such that Next*(1, a) pattern a (_,_"b + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query25)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query26)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_, _"3 + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query27)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent* (5, s) such that Modifies (s, "var3")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query28)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Uses (a, "c") pattern a (_,_"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query29)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select a such that Uses(i, "var1") such that Parent* (i, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query30)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, a) pattern a ("sum",_"var4"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query31)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, "var1") such that Next*(1, a) pattern a ("sum",_"var1*var2"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query32)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next(i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query33)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next* (i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query34)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                stmt s; assign b;
                Select b such that Next*(1, b) such that Uses (b, "c") pattern b (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("2, 3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query35)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"a+b"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple2_Query36)
        {
            initializeSimple2();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"b*c"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query01)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent (s, 10)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query02)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent (r, 18)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query03)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Parent* (i, 13)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query04)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                while w; call c;
                Select w such that Parent* (w, c)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query05)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Parent* (s, a) pattern a ("a",_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query06)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("exp, read");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query07)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies (8, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("var3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query08)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Modifies (w, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query09)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies (p, "g")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query10)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                if i;
                Select i such that Uses (i, "b")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query11)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i such that Uses (i, "c") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query12)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p pattern a (v, _"c"_) such that Uses (p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("exp");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query13)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; procedure p; variable v;
                Select p such that Uses (p, v) pattern a (v, _"var1"_) 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("exp");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query14)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Modifies(s, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 17");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query15)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies(p, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("exp, read");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query16)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select i pattern a (_,_"var1"_) such that Modifies (i, "var1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query17)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 4, 9, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query18)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a (_, _"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query19)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                procedure p; assign a;
                Select p such that Uses(p, "c")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("exp");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query20)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses (s, "a") 
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 4, 5, 8, 9, 12, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query21)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses(s, "a") such that Modifies (s, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query22)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s; if i;
                Select s such that Uses(s, "a") such that Modifies (s, "a") such that Parent* (i, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query23)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select s such that Next(2, s) pattern a (_,_"c + b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query24)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s; assign a;
                Select a such that Next*(1, a) pattern a (_,_"b + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query25)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query26)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent (5, a) pattern a (_, _"3 + c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query27)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent* (5, s) such that Modifies (s, "var3")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query28)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Uses (a, "c") pattern a (_,_"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query29)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                if i; assign a;
                Select a such that Uses(i, "var1") such that Parent* (i, a) pattern a (_,_"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query30)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, a) pattern a ("sum",_"var4"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query31)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; procedure p;
                Select a such that Uses (p, "var1") such that Next*(1, a) pattern a ("sum",_"var1*var2"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query32)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next(i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query33)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; if i;
                Select a pattern a (_,_"a+b"_) such that Next* (i, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query34)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                stmt s; assign b;
                Select b such that Next*(1, b) such that Uses (b, "c") pattern b (_, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 4, 9, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query35)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"a+b"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Simple3_Query36)
        {
            initializeSimple3();

            // create the input string
            std::string query = R"(
                assign a; assign b;
                Select b such that Next* (a, b) pattern a (_,_"b*c"_) pattern b (_,_"a +b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

    // Some private helper functions can be added below.
    private:
        static void initializeSource(const std::string& source) {
            SourceProcessor sp;
            sp.process(source);
        }

        static void initializeCode5() {
            std::string source = R"(
                procedure main {
                  flag = 0;
                  call computeCentroid;
                  call printResults;
                }
                procedure readPoint {
                  read x;
                  read y;
                }
                procedure printResults {
                  print flag;
                  print cenX;
                  print cenY;
                  print normSq;
                }
                procedure computeCentroid {
                  count = 0;
                  cenX = 0;
                  cenY = 0;
                  call readPoint;
                  while ((x * x + y * y) != 0) {
                    count = count + 1;
                    cenX = cenX + x;
                    cenY = cenY + y;
                    call readPoint;
                  }
                  if (count == 0) then {
                    flag = 1;
                  } else {
                    cenX = cenX / count;
                    cenY = cenY / count;
                  }
                  normSq = cenX * cenX + cenY * cenY;
                }
            )";
            initializeSource(source);
        }

        static void initializeCode6() {
            std::string source = R"(
                procedure First {
                read x;
                read z;
                call Second; }

                procedure Second {
                  x = 0;
                  i = 5;
                  while (i != 0) {
                    x = x + 2 * y;
                    call Third;
                    i = i - 1; }
                  if (x == 1) then {
                    x = x+1; }
                  else {
                    z = 1; }
                  z = z + x + i;
                  y = z + 2;
                  x = x * y + z; }

                procedure Third {
                  z = 5;
                  v = z;
                  print v; }
            )";
            initializeSource(source);
        }

        static void initializeSimple1() {
            std::string source = R"(
                procedure p1 {
                  read var1;
                  read var2;
                  call read;
                  while ((a + b) * c + d / (e - f) % g > 0) {
                    var1 = var1 + var2;
                    print var1;
                    if (var1 < var2) then {
                      var1 = var1 + var1;
                    } else {
                      if (a <= b) then {
                        a = a + c;
                        call print;
                        while (10 > b) {
                          if (c < var1) then {} else {}
                        }
                      } else {}
                    }
                  }
                  call print;
                }
                procedure read {
                  read a;
                  read b;
                  read c;
                  read d;
                  read e;
                  read f;
                  read g;
                }
                procedure print {
                  print a;
                  print b;
                  print var1;
                  print var2;
                }
            )";
            initializeSource(source);
        }

        static void initializeSimple2() {
            std::string source = R"(
                procedure modify {
                  call read;
                  a = a + b / c;
                  c = (b + c) / d;
                  read var1;
                  if (var1 < a + c) then {
                    call print;
                    var1 = var1;
                  } else {}
                  while ((b + c) <= (a - var1)) {
                    call print;
                  }
                }
                procedure read {
                  read a;
                  read b;
                  read c;
                  read d;
                }
                procedure print {
                  call read;
                  print a;
                  print b;
                }
            )";
            initializeSource(source);
        }

        static void initializeSimple3() {
            std::string source = R"(
                procedure exp {
                  call read;
                  read var3;
                  var3 = var1 + var2 / (a + b * c);
                  var2 = (a - (b + c) % (a / (var1 + var2) - d) + b) / c;
                  if (var2 != ((a - b) / (c + a * var1 * (var3 - d)))) then {
                    print var2;
                    print var1;
                    var3 = a + 1;
                    b = b + 1 + 2 + 3 + c / a;
                    while ((va1 + var2) / d >= 1234) {}
                  } else {
                    var4 = 4321;
                    while (var4 <= c / (a + b) % var1) {
                      print var4;
                    }
                  }
                  sum = a + b + (c - var1 * var2) % var3;
                }
                procedure read {
                  read a;
                  read b;
                  read c;
                  read d;
                  read var1;
                  read var2;
                }
            )";
            initializeSource(source);
        }

        // method to generate tokenized test output
        static void generateTestOutput(const std::string& input, std::string& testOutput)
        {
            // evaluate a query
            std::vector<std::string> output;
            QueryProcessor qp;
            qp.evaluate(input, output);

            // reset test output
            testOutput = "";

            for (size_t i = 0; i < output.size(); i++) {
                if (i != 0) {
                    testOutput.append(", ");
                }
                testOutput.append(output[i]);
            }
        }
    };
}
