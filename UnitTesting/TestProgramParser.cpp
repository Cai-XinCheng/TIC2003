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

        TEST_METHOD(CheckParseSource_Simple1)
        {
            // create the input string
            std::string testInput = R"(
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

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput =
R"(procedure p1 {
  read var1;
  read var2;
  call read;
  while (((((a) + (b)) * (c)) + (((d) / ((e) - (f))) % (g))) > (0)) {
    var1 = ((var1) + (var2));
    print var1;
    if ((var1) < (var2)) then {
      var1 = ((var1) + (var1));
    } else {
      if ((a) <= (b)) then {
        a = ((a) + (c));
        call print;
        while ((10) > (b)) {
          if ((c) < (var1)) then {
          } else {
          }
        }
      } else {
      }
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

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckParseSource_Simple2)
        {
            // create the input string
            std::string testInput = R"(
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

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput =
R"(procedure modify {
  call read;
  a = ((a) + ((b) / (c)));
  c = (((b) + (c)) / (d));
  read var1;
  if ((var1) < ((a) + (c))) then {
    call print;
    var1 = (var1);
  } else {
  }
  while (((b) + (c)) <= ((a) - (var1))) {
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

            // Logger messages can be viewed in the Test Explorer 
            // under "open additional output for this result" for each test case
            TestHelper::LogActualAndExpected(testOutput, expectedOutput, true);

            // compare the testOutput with expected output
            Assert::IsTrue(testOutput == expectedOutput);

            // The test output should match with the expected output 
            // and hence the assertion would be true.
        }

        TEST_METHOD(CheckParseSource_Simple3)
        {
            // create the input string
            std::string testInput = R"(
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

            // create the test output string from the query
            std::string testOutput;
            generateTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput =
R"(procedure exp {
  call read;
  read var3;
  var3 = ((var1) + ((var2) / ((a) + ((b) * (c)))));
  var2 = ((((a) - (((b) + (c)) % (((a) / ((var1) + (var2))) - (d)))) + (b)) / (c));
  if ((var2) != (((a) - (b)) / ((c) + (((a) * (var1)) * ((var3) - (d)))))) then {
    print var2;
    print var1;
    var3 = ((a) + (1));
    b = (((((b) + (1)) + (2)) + (3)) + ((c) / (a)));
    while ((((va1) + (var2)) / (d)) >= (1234)) {
    }
  } else {
    var4 = (4321);
    while ((var4) <= (((c) / ((a) + (b))) % (var1))) {
      print var4;
    }
  }
  sum = (((a) + (b)) + (((c) - ((var1) * (var2))) % (var3)));
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
