#include "stdafx.h"
#include "../source/Tokenizer.h"
#include "../source/ExpressionParser.h"
#include <format>

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
                {"x", "(x)", "x"},
                {"(x)", "(x)", "x"},

                {"5", "(5)", ""},
                {"(5)", "(5)", ""},

                {"x + z", "((x) + (z))", "x, z"},
                {"((x) + (z))", "((x) + (z))", "x, z"},

                {"x * z", "((x) * (z))", "x, z"},
                {"((x) * (z))", "((x) * (z))", "x, z"},

                {"x + y + z", "(((x) + (y)) + (z))", "x, y, z"},
                {"(((x) + (y)) + (z))", "(((x) + (y)) + (z))", "x, y, z"},

                {"x + z * 5", "((x) + ((z) * (5)))", "x, z"},
                {"((x) + ((z) * (5)))", "((x) + ((z) * (5)))", "x, z"},

                {"z * 5 + x", "(((z) * (5)) + (x))", "z, x"},
                {"(((z) * (5)) + (x))", "(((z) * (5)) + (x))", "z, x"},

                {"(x + z) * 5", "(((x) + (z)) * (5))", "x, z"},
                {"(((x) + (z)) * (5))", "(((x) + (z)) * (5))", "x, z"},

                {"v + x * y + z * t", "(((v) + ((x) * (y))) + ((z) * (t)))", "v, x, y, z, t"},
                {"(((v) + ((x) * (y))) + ((z) * (t)))", "(((v) + ((x) * (y))) + ((z) * (t)))", "v, x, y, z, t"},

                {"x * y * z + a", "((((x) * (y)) * (z)) + (a))", "x, y, z, a"},
                {"((((x) * (y)) * (z)) + (a))", "((((x) * (y)) * (z)) + (a))", "x, y, z, a"},

                {"x * (a + b) + c", "(((x) * ((a) + (b))) + (c))", "x, a, b, c"},
                {"(((x) * ((a) + (b))) + (c))", "(((x) * ((a) + (b))) + (c))", "x, a, b, c"},
            };

            // test cases
            testParseCases(expressionAndExpectedOutputs);
        }

        // Some private helper functions can be added below.
    private:
        // method to generate tokenized test output
        static void getTestResult(const std::string& input, std::string& expression, std::vector<std::string>& variables)
        {
            // tokenize the expression
            Tokenizer tk;
            std::vector<std::string> tokens;
            tk.tokenize(input, tokens);

            // parse the AST
            ExpressionParser parser;
            ExpressionNode* expressionNode = parser.parse(tokens);

            try {
                expression = expressionNode->toString();
                variables = expressionNode->getVariables();
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
                std::string expression;
                std::vector<std::string> variables;
                getTestResult(item.at(0), expression, variables);

                std::string variableOutput;
                for (size_t i = 0; i < variables.size(); i++) {
                    if (i != 0) {
                        variableOutput += ", ";
                    }
                    variableOutput += variables[i];
                }

                std::string testOutput = std::format("Expression: {}\nVariables: {}", expression, TestHelper::reorderOutput(variableOutput));
                std::string expectedOutput = std::format("Expression: {}\nVariables: {}", item.at(1), TestHelper::reorderOutput(item.at(2)));
                TestHelper::LogActualAndExpected(testOutput, expectedOutput, false, item.at(0).c_str());
                Assert::IsTrue(testOutput == expectedOutput);
            }
        }
    };
}
