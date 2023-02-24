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
        TEST_METHOD(CheckTransformQuery_ExampleQ1)
        {
            // create the input string
            std::string testInput = R"(
                procedure p;
                Select p
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT p.procedureName";
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

        TEST_METHOD(CheckTransformQuery_ExampleQ2)
        {
            // create the input string
            std::string testInput = R"(
                variable v;
                Select v
            )";

            // create the test output string from the tokens
            std::string testOutput;
            getTestOutput(testInput, testOutput);

            // create the expected output string
            std::string expectedOutput = "SELECT v.name";
            expectedOutput += " FROM variables AS v";
            expectedOutput += "";

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
            testOutput = PQL2SQLTransformer::transform(selectClause);
        }
    };
}
