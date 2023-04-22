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

        TEST_METHOD(CheckSPA_Midterm_Query01)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s, s1; assign a, a1; while w; if ifs; variable v, v1; procedure p; constant c; read re; print pn;
                Select a
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 5, 8, 10, 12, 13");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query02)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select c
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 0, 15, 123");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query03)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select v such that Modifies(2, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("ByeWorld");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query04)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select pn such that Modifies(8, "y")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 11");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query05)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select v such that Uses(4, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query06)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select a such that Uses(a, "x")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5, 10, 12, 13");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query07)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select s such that Parent(s, 7)
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

        TEST_METHOD(CheckSPA_Midterm_Query08)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select s such that Parent*(s, 10)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("7, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query09)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select v pattern a(v,"y + 1")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("x");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query10)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select a such that Uses(a, v) pattern a("x", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 12");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Midterm_Query11)
        {
            initializeMidterm();

            // create the input string
            std::string query = R"(
                stmt s; assign a; while w; if ifs; variable v;procedure p; constant c; read re; print pn;
                Select v such that Modifies(10, v) pattern a("z", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query01)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query02)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 6, 7, 8, 9, 10, 13, 14, 15, 17, 19, 20, 21, 23, 24, 25, 27, 28, 30, 31, 32, 33, 12, 16, 22, 29, 4, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query03)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                constant c;
                Select c
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5, 2, 3, 7, 1, 0");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query04)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                while w;
                Select w
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

        TEST_METHOD(CheckSPA_Iteration2a_Query05)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs
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

        TEST_METHOD(CheckSPA_Iteration2a_Query06)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                read re; 
                Select re
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("11, 18");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query07)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                print pn;
                Select pn
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("26");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query08)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("proc");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query09)
        {
            initializeIteration2a();

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

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y, z, bx");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query10)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a(_, _"i-1"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("6, 14, 17, 24, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query11)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a(_, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 6, 7, 8, 9, 10, 13, 14, 15, 17, 19, 20, 21, 23, 24, 25, 27, 28, 30, 31, 32, 33, 12, 16, 22, 29, 4, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query12)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;  variable v;
                Select a pattern a(v, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 6, 7, 8, 9, 10, 13, 14, 15, 17, 19, 20, 21, 23, 24, 25, 27, 28, 30, 31, 32, 33, 12, 16, 22, 29, 4, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query13)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("i", _"i-1"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("6, 14, 24, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query14)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("i", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 6, 9, 10, 14, 19, 20, 24, 25, 31, 32");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query15)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent(12, a) pattern a("i", _"i-1"_)
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

        TEST_METHOD(CheckSPA_Iteration2a_Query16)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v; assign a, a1;
                Select v such that Modifies(a, v) pattern a1(v, _"i+1"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query17)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v; assign a;
                Select a such that Uses(3, v) pattern a(v, _"i-1"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("6, 14, 24, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query18)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v; assign a, a1;
                Select v such that Modifies(a, v) pattern a1("z", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y, z, bx");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query19)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; variable v;
                Select s such that Modifies(s, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query20)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; variable v;
                Select v such that Modifies(s, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y, z, bx");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query21)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; 
                Select s such that Modifies(s, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query22)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; 
                Select s such that Modifies(s, "i")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 6, 9, 10, 14, 19, 20, 24, 25, 31, 32");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query23)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies(6, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query24)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p; variable v;
                Select p such that Modifies(p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("proc");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query25)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p; variable v;
                Select v such that Modifies(p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y, z, bx");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query26)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p such that Modifies(p, "i")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("proc");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query27)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                read re; variable v;
                Select re such that Modifies(re, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("11, 18");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query28)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                read re; variable v;
                Select v such that Modifies(re, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("x, y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query29)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                read re; 
                Select re such that Modifies(re, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("11, 18");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query30)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; variable v;
                Select s such that Uses(s, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 6, 7, 8, 9, 14, 17, 19, 20, 21, 24, 25, 26, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query31)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; variable v;
                Select v such that Uses(s, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query32)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; 
                Select s such that Uses(s, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 6, 7, 8, 9, 14, 17, 19, 20, 21, 24, 25, 26, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query33)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s; 
                Select s such that Uses(s, "i")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 6, 9, 14, 17, 19, 21, 24, 26, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query34)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Uses(3, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query35)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p; variable v;
                Select p such that Uses(p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("proc");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query36)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                procedure p; variable v;
                Select v such that Uses(p, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query37)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                print pn; variable v;
                Select pn such that Uses(pn, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("26");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query38)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                print pn; variable v;
                Select v such that Uses(pn, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query39)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select a such that Uses(a, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("3, 6, 7, 8, 9, 14, 17, 19, 20, 21, 24, 25, 31");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query40)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select v such that Uses(a, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("i, x, y");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query41)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Uses("proc", "i")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("bx, i, x, y, z");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2a_Query42)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s, s1;
                Select s such that Parent(s, s1)
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

        TEST_METHOD(CheckSPA_Iteration2a_Query43)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s, s1;
                Select s1 such that Parent*(s, s1)
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

        TEST_METHOD(CheckSPA_Iteration2a_Query44)
        {
            initializeIteration2a();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent(s, _)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query01)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 20, 21, 3, 4, 5, 6, 7, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query02)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                read r;
                Select r
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 11, 15, 17, 20, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query03)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 18, 21, 3, 7, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query04)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w;
                Select w
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("16, 4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query05)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs
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

        TEST_METHOD(CheckSPA_Iteration2b_Query06)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a;
                Select a
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 13, 14, 19, 2, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query07)
        {
            initializeIteration2b();

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

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c, code9, coding7, d, test001, test002, test02");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query08)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                constant c;
                Select c
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 20, 30");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query09)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("NonNesting01");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query10)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent(_, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 11, 15, 17, 20, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query11)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent(_, 3)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query12)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent(8, _)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query13)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent(_, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 13, 14, 19, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query14)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent(s, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("16, 4, 8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query15)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                constant c;
                Select c such that Parent(8, 12)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 20, 30");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query16)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs; stmt s;
                Select ifs such that Parent(ifs, s)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query17)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w; print pr;
                Select pr such that Parent(w, pr)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("18, 21, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query18)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent(4, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5, 6, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query19)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent(w, 18)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("16");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query20)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Parent*(_, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c, code9, coding7, d, test001, test002, test02");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query21)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr such that Parent*(_, 3)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query22)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent*(16, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 11, 15, 17, 20, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query23)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent*(_, w)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query24)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent*(ifs, _)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query25)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Parent*(4, 10)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query26)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs; print p;
                Select ifs such that Parent*(ifs, p)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query27)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs; print p;
                Select p such that Parent*(ifs, p)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query28)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent*(8, ifs)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query29)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent*(w, 7)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query30)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Modifies(s, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 10, 13, 14, 16, 17, 4, 5, 8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query31)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies(4, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, test02");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query32)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Modifies(r, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 11, 15, 17, 20, 5");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query33)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                while w; variable v;
                Select w such that Modifies(w, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("16, 4");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query34)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses(s, "b")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 13, 14, 16, 18, 2, 4, 6, 7, 8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query35)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Uses(8, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c, coding7, d, test001");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query36)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr such that Uses(pr, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 18, 21, 3, 7, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query37)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                if ifs; variable v;
                Select ifs such that Uses(ifs, v)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query38)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a(_, _"30%d"_)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query39)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select v pattern a(v, "30")
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

        TEST_METHOD(CheckSPA_Iteration2b_Query40)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("d", _"20"_)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query41)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("test001", "a + b + c + d")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("2");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query42)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; if ifs;
                Select a such that Parent(ifs, a) pattern a("a", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 13, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query43)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; while w; variable v;
                Select v  such that Parent*(w, a) pattern a(v, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("test02");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query44)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; while w; variable v;
                Select v such that Modifies(w, v) pattern a(v, _"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query45)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; stmt s; variable v;
                Select s such that Modifies(s, _) pattern a(v, _"a-b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 10, 11, 13, 14, 15, 16, 17, 19, 2, 20, 4, 5, 6, 8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query46)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select a such that Uses(a, v) pattern a("a", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 13, 14");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2b_Query47)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select v such that Uses(a, v) pattern a(_, _"a"_)
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

        TEST_METHOD(CheckSPA_Iteration2b_Query48)
        {
            initializeIteration2b();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select w such that Parent*(w, a) pattern a("test002", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("16");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query01)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 3, 4, 5, 6, 7, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query02)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                read r;
                Select r
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query03)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("13, 16, 18, 19, 3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query04)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w;
                Select w
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 4, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query05)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("17, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query06)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a;
                Select a
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 11, 14, 15, 2, 5, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query07)
        {
            initializeIteration2c();

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

            std::string expectedOutput = TestHelper::reorderOutput("a, add, b, c, d, negative, positive");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query08)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                constant c;
                Select c
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("0, 10, 20, 30");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query09)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("NestedWhileIf");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query10)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent(_, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query11)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent(_, 19)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 4, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query12)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent(12, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("17, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query13)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a;
                Select a such that Parent(_, a)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 11, 14, 5, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query14)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent(s, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 17, 4, 6, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query15)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                constant c;
                Select c such that Parent(4, 7)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query16)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs; while w;
                Select ifs such that Parent(ifs, w)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query17)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w; print pr;
                Select pr such that Parent(w, pr)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("13");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query18)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Parent(4, s)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("5, 6, 8");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query19)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent(w, 14)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query20)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Parent*(_, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, add, b, c, d, negative, positive");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query21)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr such that Parent*(_, 14)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("13, 16, 18, 19, 3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query22)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Parent*(8, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query23)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent*(_, w)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query24)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent*(ifs, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("17, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query25)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Parent*(4, 10)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, add, b, c, d, negative, positive");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query26)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs; while w;
                Select ifs such that Parent*(ifs, w)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query27)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs; while w;
                Select w such that Parent*(ifs, w)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("12");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query28)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs;
                Select ifs such that Parent*(4, ifs)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query29)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w;
                Select w such that Parent*(w, 7)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query30)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Modifies(s, "a")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 4, 5, 6, 7");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query31)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Modifies(5, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query32)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                read r;
                Select r such that Modifies(r, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query33)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                while w; variable v;
                Select w such that Modifies(w, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query34)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                stmt s;
                Select s such that Uses(s, "b")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("10, 11, 14, 15, 4, 5, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query35)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                variable v;
                Select v such that Uses(4, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query36)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                print pr;
                Select pr such that Uses(pr, _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("13, 16, 18, 19, 3");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query37)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                if ifs; variable v;
                Select ifs such that Uses(ifs, v)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("17, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query38)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a(_, _"d"_)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query39)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select v pattern a(v, "10")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query40)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("d", _"20"_)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query41)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a;
                Select a pattern a("add", "a * b * c")
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

        TEST_METHOD(CheckSPA_Iteration2c_Query42)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; if ifs;
                Select a such that Parent(ifs, a) pattern a("a", _)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query43)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; while w; variable v;
                Select v  such that Parent*(w, a) pattern a(v, _"b"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, c, d");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query44)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; while w; variable v;
                Select v such that Modifies(w, v) pattern a(v, _"b+c"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query45)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; stmt s; variable v;
                Select s such that Modifies(s, _) pattern a(v, "10")
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("1, 10, 11, 14, 15, 2, 4, 5, 6, 7, 8, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query46)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select a such that Uses(a, v) pattern a("a", _)
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

        TEST_METHOD(CheckSPA_Iteration2c_Query47)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; variable v;
                Select v such that Uses(a, v) pattern a(_, _"a"_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration2c_Query48)
        {
            initializeIteration2c();

            // create the input string
            std::string query = R"(
                assign a; while w;
                Select w such that Parent*(w, a) pattern a("a", _)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("4, 6");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration3_query12100)
        {
            initializeIteration3();

            // create the input string
            std::string query = R"(
                call cl; 
                Select cl such that Next*(_, cl)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("18, 23, 26, 5, 9");

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckSPA_Iteration3_query13410)
        {
            initializeIteration3();

            // create the input string
            std::string query = R"(
                stmt s, s1, s2, s3; assign a, a1, a2, a3; while w; if ifs; variable v, v1, v2, v3; procedure p, q; constant c; call cl; read re; print pn;
                Select v such that Next*(17, 14) such that Uses(s2, v) such that Modifies(s2, v) pattern a(_,_)
            )";

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(query, testOutput);
            testOutput = TestHelper::reorderOutput(testOutput);

            // create the expected output string

            std::string expectedOutput = TestHelper::reorderOutput("a, b, c, count, s, x, y");

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

        static void initializeMidterm() {
            std::string source = R"(
                procedure A {
                  print HelloWorld;
                  read ByeWorld;
                  read x;
                  x = y + 1;
                  y = x * (x + 1);
                  while (x < 0) {
                    if (HelloWorld > 15) then {
                      y = y + 123;
                      read z;
                    }
                    else {
                      y = (x / y * z);
                      print z;
                    }
                  }
                  x = x + y + z;
                  z = x % 123;
                  read y;
                }
            )";
            initializeSource(source);
        }

        static void initializeIteration2a() {
            std::string source = R"(
                procedure proc {
	                i = 5;
	                x = 2;
	                y = x + 1 + i* 3/(5-7);
	                bx = 0;
	                bx = 0;
	                i = i - 1;
	                z = x;
	                x = y;
	                i = i + 1;
	                i = 5;
	                read x;
	                bx = 0;
	                y = 3;
	                i = i - 1;
	                y = 3; 
	                bx = 0;
	                z = i - 1; 
	                read y;			
	                i = i + 1; 
	                i = x + y * 3;
	                y = y + x + i; 
	                bx = 0;
	                y = 3;
	                i = i - 1;
	                i = x;
	                print i;
	                y = 3;
	                y= 3;
	                bx = 0;
	                y = 3;
	                i = i - 1;
	                i = 5; 
	                y= 3;
                }
            )";
            initializeSource(source);
        }

        static void initializeIteration2b() {
            std::string source = R"(
                procedure NonNesting01 {
                    read a;
                    test001 =  a + b + c + d;
                    print code9;

                    while (10 < a) {
                        read a;
                        test02 = 20 + (a - b) * (c % d);
                        print b;
                    }

                    if (10 > a) then {
                        print coding7;
                        a = b + c + d;
                        read coding7;
                    } else {
                        print test001;
                        a = b + c + d;
                        a = b + c + d;
                        read b;
                    }

                    while (a > c) {
                        read a;
                        print b;
                        test002 = (c / 30 % d);
                        read b;
                        print a;
                    }
                }
            )";
            initializeSource(source);
        }

        static void initializeIteration2c() {
            std::string source = R"(
                procedure NestedWhileIf {
                    read a;
                    b = 20;
                    print d;

                    while (a < 30) {
                        a = b + c;
                        while (a < 10) {
                            a = 10;
                        }
                        if (a > 10) then {
                            if (c < 30) then {
                                d = b;
                            } else {
                                c = a + b;
                            }
                        } else {
                            while (a < 10) {
                                print c;
                            }
                            c = a + b;
                        }
                    }

                    add = a * b * c;                
                    print add;
                    if (add < 0) then {
                        print negative;
                    } else {
                        print positive;
                    }
                }
            )";
            initializeSource(source);
        }

        static void initializeIteration3() {
            std::string source = R"(
                procedure main {
	                i = 5;
	                x = 2;
	                y = x+(1+i)*3/(5-7);
	                while (i < x) {
		                call call1;
		                while (i > 0) {
			                y = 3;
			                print i;
		                }
	                }
	                call call4;
	                read a;
	                print answer;
                }

                procedure call1 {
	                call call2;
	                while (epsilon < (b-a)) {
	                        c = (a+b)/20;
	                        s = x*c+y-c/2*c;
	                        read s;
	                        a = s+2; 
	                }
	                call call5;
	                count = count+1;
	                b = s; 
                }

                procedure call2 {
	                y = i-1+y+x;
	                count = 0;
	                call call3;
                }

                procedure call3 {
	                if(x > 0) then {
            	                y = 3;
	                } else {
		                call call4;
		                while(x > 0) {
			                b = 3+re; 
		                }
	                }
	                read b;
                }

                procedure call4 {
	                call call5;
                }

                procedure call5 {
	                x = 5*(5*(5+55)*x/55);
                }

                procedure call6 {
	                read pn;
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
