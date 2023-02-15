#include "stdafx.h"
#include "../source/Tokenizer.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
            string testInput = "procedure p;Select p";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "procedure$p$;$Select$p$"; 

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: "); 
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
 
            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ2)
        {
            // create the input string
            string testInput = "variable v;Select v";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "variable$v$;$Select$v$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ3)
        {
            // create the input string
            string testInput = "stmt s;Select s such that Next* (6, s)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "stmt$s$;$Select$s$such$that$Next*$($6$,$s$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ4)
        {
            // create the input string
            string testInput = "variable v;Select v such that Modifies(6, v)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "variable$v$;$Select$v$such$that$Modifies$($6$,$v$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ5)
        {
            // create the input string
            string testInput = "variable v;Select  v such that Uses(14, v)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "variable$v$;$Select$v$such$that$Uses$($14$,$v$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ6)
        {
            // create the input string
            string testInput = "assign a; while w;Select a such that Parent* (w, a)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "assign$a$;$while$w$;$Select$a$such$that$Parent*$($w$,$a$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ7)
        {
            // create the input string
            string testInput = "stmt s;Select s such that Parent(s, 7)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "stmt$s$;$Select$s$such$that$Parent$($s$,$7$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ8)
        {
            // create the input string
            string testInput = R"!(variable v; procedure p;Select p such that  Modifies(p, "x"))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"(variable$v$;$procedure$p$;$Select$p$such$that$Modifies$($p$,$"x"$)$)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ9)
        {
            // create the input string
            string testInput = "procedure p, q;Select p such that Calls(p, _)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "procedure$p$,$q$;$Select$p$such$that$Calls$($p$,$_$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ10)
        {
            // create the input string
            string testInput = R"!(procedure p;Select  p such that Calls* (p, "Third"))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(procedure$p$;$Select$p$such$that$Calls*$($p$,$"Third"$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ11)
        {
            // create the input string
            string testInput = "procedure p, q; Select <p, q> such that Calls(p, q)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "procedure$p$,$q$;$Select$<$p$,$q$>$such$that$Calls$($p$,$q$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ12)
        {
            // create the input string
            string testInput = R"!(assign a;Select a pattern a("x", _))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($"x"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ13)
        {
            // create the input string
            string testInput = R"!(assign a;Select a pattern a ( _ , _"count + 1"_))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($_$,$_"count + 1"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ14_1)
        {
            // create the input string
            string testInput = R"!(assign a;Select a pattern a ( "normSq" , _"cenX * cenX"_))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$Select$a$pattern$a$($"normSq"$,$_"cenX * cenX"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ14_2)
        {
            // create the input string
            string testInput = R"!(assign newa;Select newa pattern newa ( "normSq" , _"cenX * cenX"_))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$newa$;$Select$newa$pattern$newa$($"normSq"$,$_"cenX * cenX"_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ15)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select w such that Parent* (w, a) pattern a ("count", _))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$w$such$that$Parent*$($w$,$a$)$pattern$a$($"count"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ16)
        {
            // create the input string
            string testInput = "assign a; variable v;Select a such that Uses(a, v) pattern a(v, _)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "assign$a$;$variable$v$;$Select$a$such$that$Uses$($a$,$v$)$pattern$a$($v$,$_$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ17_1)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a  pattern a ("x", _) such that Uses (a, "x"))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"x"$,$_$)$such$that$Uses$($a$,$"x"$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ17_2)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a such that Uses (a, "x") pattern a ("x", _))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Uses$($a$,$"x"$)$pattern$a$($"x"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ18_1)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a such that Parent* (w, a) pattern a ("count", _))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Parent*$($w$,$a$)$pattern$a$($"count"$,$_$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ18_2)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a pattern a ("count", _) such that Parent* (w, a))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"count"$,$_$)$such$that$Parent*$($w$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ19)
        {
            // create the input string
            string testInput = "stmt s;Select n such that Next* (5, s) such that Next* (s, 12)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "stmt$s$;$Select$n$such$that$Next*$($5$,$s$)$such$that$Next*$($s$,$12$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ20_1)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a pattern a ("x", _) such that Parent* (w, a) such that Next* (1, a))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$pattern$a$($"x"$,$_$)$such$that$Parent*$($w$,$a$)$such$that$Next*$($1$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ20_2)
        {
            // create the input string
            string testInput = R"!(assign a; while w;Select a such that Modifies (a, "x") such that Parent* (w, a) such that Next* (1, a))!";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = R"!(assign$a$;$while$w$;$Select$a$such$that$Modifies$($a$,$"x"$)$such$that$Parent*$($w$,$a$)$such$that$Next*$($1$,$a$)$)!";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeQuery_ExampleQ21)
        {
            // create the input string
            string testInput = "while w1, w2, w3;Select <w1, w2, w3> such that Parent* (w1, w2) such that Parent* (w2, w3)";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            // create the expected output string
            string expectedOutput = "while$w1$,$w2$,$w3$;$Select$<$w1$,$w2$,$w3$>$such$that$Parent*$($w1$,$w2$)$such$that$Parent*$($w2$,$w3$)$";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);
        }

        TEST_METHOD(CheckTokenizeProgram)
        {
            string testInput = "procedure echo { read num1; index = 1001; print index; print num1; }";

            // create the test output string from the tokens
            string testOutput;
            getTokenizedTestOutput(testInput, testOutput);

            string expectedOutput = "procedure$echo${$read$num1$;$index$=$1001$;$print$index$;$print$num1$;$}$";

            Logger::WriteMessage("Test Output: ");
            Logger::WriteMessage(testOutput.c_str());
            Logger::WriteMessage("Expected Output: ");
            Logger::WriteMessage(expectedOutput.c_str());

            Assert::IsTrue(testOutput == expectedOutput);
        }

    // Some private helper functions can be added below.
    private:
        // method to get tokenized test output 
        void getTokenizedTestOutput(const string& input, string& testOutput) const
        {
            // run the tokenizer method
            Tokenizer tk;
            vector<string> tokens;
            tk.tokenize(input, tokens);

            // reset test output
            testOutput = "";

            for (string token : tokens)
            {
                testOutput.append(token + "$");
            }
        }
    };
}
