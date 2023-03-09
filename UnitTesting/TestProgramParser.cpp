#include "stdafx.h"
#include "../source/Tokenizer.h"
#include "../source/ProgramParser.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace ProgramParserTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestProgramParser)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckParseSource_Code5)
        {
            // create the input string
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

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput =
R"(procedure main {
  flag = (0);
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
  count = (0);
  cenX = (0);
  cenY = (0);
  call readPoint;
  while ((((x) * (x)) + ((y) * (y))) != (0)) {
    count = ((count) + (1));
    cenX = ((cenX) + (x));
    cenY = ((cenY) + (y));
    call readPoint;
  }
  if ((count) == (0)) then {
    flag = (1);
  } else {
    cenX = ((cenX) / (count));
    cenY = ((cenY) / (count));
  }
  normSq = (((cenX) * (cenX)) + ((cenY) * (cenY)));
}
)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckParseSource_Code6)
        {
            // create the input string
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

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput =
R"(procedure First {
  read x;
  read z;
  call Second;
}

procedure Second {
  x = (0);
  i = (5);
  while ((i) != (0)) {
    x = ((x) + ((2) * (y)));
    call Third;
    i = ((i) - (1));
  }
  if ((x) == (1)) then {
    x = ((x) + (1));
  } else {
    z = (1);
  }
  z = (((z) + (x)) + (i));
  y = ((z) + (2));
  x = (((x) * (y)) + (z));
}

procedure Third {
  z = (5);
  v = (z);
  print v;
}
)";

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

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
            // tokenize the query
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // parse the AST
            ProgramParser parser(tokens);
            Program program = parser.parse();

            testOutput = program.toString();
        }
    };
}
