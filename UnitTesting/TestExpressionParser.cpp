#include "stdafx.h"
#include "../source/Tokenizer.h"
#include "../source/ExpressionParser.h"

using Assert = Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace ExpressionParserTests
{
    // Each cpp is a set of test cases for a specific component.
    TEST_CLASS(TestExpressionParser)
    {
    public:
        // Each test method is a separate test case. The name should be unique and meaningful.
        TEST_METHOD(CheckParseExpressions)
        {
            // expression and expected outputs
            std::vector<std::vector<std::string>> expressionAndExpectedOutputs = {
                {"x", "(x)"},
                {"(x)", "(x)"},

                {"5", "(5)"},
                {"(5)", "(5)"},

                {"x + z", "((x) + (z))"},
                {"((x) + (z))", "((x) + (z))"},

                {"x * z", "((x) * (z))"},
                {"((x) * (z))", "((x) * (z))"},

                {"x + y + z", "(((x) + (y)) + (z))"},
                {"(((x) + (y)) + (z))", "(((x) + (y)) + (z))"},

                {"x + z * 5", "((x) + ((z) * (5)))"},
                {"((x) + ((z) * (5)))", "((x) + ((z) * (5)))"},

                {"z * 5 + x", "(((z) * (5)) + (x))"},
                {"(((z) * (5)) + (x))", "(((z) * (5)) + (x))"},

                {"(x + z) * 5", "(((x) + (z)) * (5))"},
                {"(((x) + (z)) * (5))", "(((x) + (z)) * (5))"},

                {"v + x * y + z * t", "(((v) + ((x) * (y))) + ((z) * (t)))"},
                {"(((v) + ((x) * (y))) + ((z) * (t)))", "(((v) + ((x) * (y))) + ((z) * (t)))"},

                {"x * y * z + a", "((((x) * (y)) * (z)) + (a))"},
                {"((((x) * (y)) * (z)) + (a))", "((((x) * (y)) * (z)) + (a))"},

                {"x * (a + b) + c", "(((x) * ((a) + (b))) + (c))"},
                {"(((x) * ((a) + (b))) + (c))", "(((x) * ((a) + (b))) + (c))"},
            };

            // test cases
            testParseCases(expressionAndExpectedOutputs);
        }

        // Some private helper functions can be added below.
    private:
        // method to generate tokenized test output
        static void generateTestOutput(const std::string& input, std::string& testOutput)
        {
            // tokenize the expression
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // parse the AST
            ExpressionParser parser;
            ExpressionNode* expressionNode = parser.parse(tokens);

            try {
                testOutput = expressionNode->toString();
            }
            catch (...) {
                delete expressionNode;
                throw;
            }
            delete expressionNode;
        }

        static void testParseCases(const std::vector<std::vector<std::string>>& cases) {
            for (std::vector<std::string> const& item : cases) {
                // create the test output string from the statements retrieved
                std::string testOutput;
                generateTestOutput(item.at(0), testOutput);

                // Logger messages can be viewed in the Test Explorer 
                // under "open additional output for this result" for each test case
                TestHelper::LogActualAndExpected(testOutput, item.at(1), false, item.at(0).c_str());

                // compare the test output with expected output
                Assert::IsTrue(testOutput == item.at(1));
            }
        }
    };
}
