#include "stdafx.h"
#include "../source/Tokenizer.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace TokenizerTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestTokenizer)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckTokenizeQuery_ExampleQ1) 
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure$p$;$Select$p$"; 

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
 
            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ2)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable$v$;$Select$v$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ3)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (6, s)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt$s$;$Select$s$such$that$Next*$($6$,$s$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ4)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Modifies (6, v)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable$v$;$Select$v$such$that$Modifies$($6$,$v$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ5)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v such that Uses (14, v)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "variable$v$;$Select$v$such$that$Uses$($14$,$v$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ6)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign$a$;$while$w$;$Select$a$such$that$Parent*$($w$,$a$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ7)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Parent (s, 7)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt$s$;$Select$s$such$that$Parent$($s$,$7$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ8)
        {
            // create the input string
            std::string testInput = R"(
                variable v; procedure p;
                Select p such that Modifies (p, "x")
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"(variable$v$;$procedure$p$;$Select$p$such$that$Modifies$($p$,$"x"$)$)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ9)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select p such that Calls (p, _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure$p$,$q$;$Select$p$such$that$Calls$($p$,$_$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ10)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p such that Calls* (p, "Third")
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(procedure$p$;$Select$p$such$that$Calls*$($p$,$"Third"$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ11)
        {
            // create the input string
            std::string testInput = R"(
                procedure p, q;
                Select <p, q> such that Calls (p, q)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "procedure$p$,$q$;$Select$<$p$,$q$>$such$that$Calls$($p$,$q$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ12)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("x", _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($"x"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ13)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a (_, _"count + 1"_)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($_$,$_"count + 1"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ14_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a;
                Select a pattern a ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($"normSq"$,$_"cenX * cenX"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ14_2)
        {
            // create the input string
            std::string testInput = R"(
                assign newa;
                Select newa pattern newa ("normSq", _"cenX * cenX"_)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$newa$;$Select$newa$pattern$newa$($"normSq"$,$_"cenX * cenX"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ15)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select w such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$w$such$that$Parent*$($w$,$a$)$pattern$a$($"count"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ16)
        {
            // create the input string
            std::string testInput = R"(
                assign a; variable v;
                Select a such that Uses (a, v) pattern a (v, _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "assign$a$;$variable$v$;$Select$a$such$that$Uses$($a$,$v$)$pattern$a$($v$,$_$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ17_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Uses (a, "x")
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"x"$,$_$)$such$that$Uses$($a$,$"x"$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ17_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Uses (a, "x") pattern a ("x", _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Uses$($a$,$"x"$)$pattern$a$($"x"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ18_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Parent* (w, a) pattern a ("count", _)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Parent*$($w$,$a$)$pattern$a$($"count"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ18_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("count", _) such that Parent* (w, a)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"count"$,$_$)$such$that$Parent*$($w$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ19)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next* (5, s) such that Next* (s, 12)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt$s$;$Select$s$such$that$Next*$($5$,$s$)$such$that$Next*$($s$,$12$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ20_1)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"x"$,$_$)$such$that$Parent*$($w$,$a$)$such$that$Next*$($1$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ20_2)
        {
            // create the input string
            std::string testInput = R"(
                assign a; while w;
                Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (1, a)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Modifies$($a$,$"x"$)$such$that$Parent*$($w$,$a$)$such$that$Next*$($1$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ21)
        {
            // create the input string
            std::string testInput = R"(
                while w1, w2, w3;
                Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "while$w1$,$w2$,$w3$;$Select$<$w1$,$w2$,$w3$>$such$that$Parent*$($w1$,$w2$)$such$that$Parent*$($w2$,$w3$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ22)
        {
            // create the input string
            std::string testInput = R"(
                assign a1, a2; while w1, w2;
                Select a1 pattern a1 ("x", _) pattern a2 ("x", _"x"_) such that Next* (a1, a2) such that Parent* (w2, a2) such that Parent* (w1, w2)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = R"!(assign$a1$,$a2$;$while$w1$,$w2$;$Select$a1$pattern$a1$($"x"$,$_$)$pattern$a2$($"x"$,$_"x"_$)$such$that$Next*$($a1$,$a2$)$such$that$Parent*$($w2$,$a2$)$such$that$Parent*$($w1$,$w2$)$)!";

            // Logger messages can be viewed in the Test Explorer
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeSource_ExampleCode1)
        {
            std::string testInput = R"(
                procedure computeAverage {

                    read num1;
                    read num2;
                    read num3;

                    sum = num1 + num2 + num3;
                    ave = sum / 3;

                    print ave;
                }
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            std::string expectedOutput = "procedure$computeAverage${$read$num1$;$read$num2$;$read$num3$;$sum$=$num1$+$num2$+$num3$;$ave$=$sum$/$3$;$print$ave$;$}$";

            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeSource_ExampleCode2)
        {
            std::string testInput = R"(
                procedure printAscending {
                    read num1;
                    read num2;
                    noSwap = 0;

                    if (num1 > num2) then {
                      temp = num1;
                      num1 = num2;
                      num2 = temp;
                    } else {
                      noSwap = 1;
                    }

                    print num1;
                    print num2;
                    print noSwap;
                }
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            std::string expectedOutput = "procedure$printAscending${$read$num1$;$read$num2$;$noSwap$=$0$;$if$($num1$>$num2$)$then${$temp$=$num1$;$num1$=$num2$;$num2$=$temp$;$}$else${$noSwap$=$1$;$}$print$num1$;$print$num2$;$print$noSwap$;$}$";

            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeSource_ExampleCode3)
        {
            std::string testInput = R"(
                procedure sumDigits {
                    read number;
                    sum = 0;

                    while (number > 0) {
                        digit = number % 10;
                        sum = sum + digit;
                        number = number / 10;
                    }

                    print sum;
                }
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            std::string expectedOutput = "procedure$sumDigits${$read$number$;$sum$=$0$;$while$($number$>$0$)${$digit$=$number$%$10$;$sum$=$sum$+$digit$;$number$=$number$/$10$;$}$print$sum$;$}$";

            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeSource_ExampleCode4AndCode5)
        {
            std::string testInput = R"(
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

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            std::string expectedOutput = "procedure$main${$flag$=$0$;$call$computeCentroid$;$call$printResults$;$}$";
            expectedOutput += "procedure$readPoint${$read$x$;$read$y$;$}$";
            expectedOutput += "procedure$printResults${$print$flag$;$print$cenX$;$print$cenY$;$print$normSq$;$}$";
            expectedOutput += "procedure$computeCentroid${$count$=$0$;$cenX$=$0$;$cenY$=$0$;$call$readPoint$;$while$($($x$*$x$+$y$*$y$)$!=$0$)${$count$=$count$+$1$;$cenX$=$cenX$+$x$;$cenY$=$cenY$+$y$;$call$readPoint$;$}$if$($count$==$0$)$then${$flag$=$1$;$}$else${$cenX$=$cenX$/$count$;$cenY$=$cenY$/$count$;$}$normSq$=$cenX$*$cenX$+$cenY$*$cenY$;$}$";

            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeSource_ExampleCode6)
        {
            std::string testInput = R"(
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

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            std::string expectedOutput = "procedure$First${$read$x$;$read$z$;$call$Second$;$}$";
            expectedOutput += "procedure$Second${$x$=$0$;$i$=$5$;$while$($i$!=$0$)${$x$=$x$+$2$*$y$;$call$Third$;$i$=$i$-$1$;$}$if$($x$==$1$)$then${$x$=$x$+$1$;$}$else${$z$=$1$;$}$z$=$z$+$x$+$i$;$y$=$z$+$2$;$x$=$x$*$y$+$z$;$}$";
            expectedOutput += "procedure$Third${$z$=$5$;$v$=$z$;$print$v$;$}$";

            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_Bug01_Expression)
        {
            // create the input string
            std::string testInput = "Next*b";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "Next$*$b$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckTokenizeQuery_Bug01_Query)
        {
            // create the input string
            std::string testInput = R"(
                stmt s;
                Select s such that Next*(6, s)
            )";

            // create the test output string from a string
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "stmt$s$;$Select$s$such$that$Next*$($6$,$s$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

    // Some private helper functions can be added below.
    private:
        // method to generate tokenized test output
        static void generateTestOutput(const std::string& input, std::string& testOutput)
        {
            // run the tokenizer method
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // reset test output
            testOutput = "";

            for (std::string token : tokens)
            {
                testOutput.append(token + "$");
            }
        }
    };
}
