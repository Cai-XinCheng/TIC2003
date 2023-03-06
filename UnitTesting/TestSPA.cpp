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
        TEST_METHOD(CheckSPA_ExampleQ1) 
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

        TEST_METHOD(CheckSPA_ExampleQ2)
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

        TEST_METHOD(CheckSPA_ExampleQ3)
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

        TEST_METHOD(CheckSPA_ExampleQ4)
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

        TEST_METHOD(CheckSPA_ExampleQ5)
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

        TEST_METHOD(CheckSPA_ExampleQ6)
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

        TEST_METHOD(CheckSPA_ExampleQ7)
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

        TEST_METHOD(CheckSPA_ExampleQ8)
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

        TEST_METHOD(CheckSPA_ExampleQ9)
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

        TEST_METHOD(CheckSPA_ExampleQ10)
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
