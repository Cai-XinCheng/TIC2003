#include "SourceProcessor.h"
#include<set>
#include<stack>
#include <numeric>


// statement number
uint32_t stmtNo = 0;

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(std::string program) {
	// initialize the database
	Database::initialize();

	// tokenize the program
	Tokenizer tk;
    std::vector<std::string> tokens;
	tk.tokenize(program, tokens);

    // a vector to store each line of statement
    std::vector<std::string> statement;

    /*
    // Debug, print out tokens
    printf("-------------------------------\n");
    for (auto const& string : tokens) {
        printf("%s\n", string.c_str());
    }
    printf("-------------------------------\n");
    */

    processToken(tokens);
}

void SourceProcessor::processToken(std::vector<std::string> token) {
    std::vector<std::string> statement;
    // a stack to store if/while information
    std::stack<std::vector<std::string>> stack;
    for (auto it = token.begin(); it != token.end(); it++) {
        if (*it == ";" || *it == "{") { // end of a statement
            std::string stmtType = statement.at(0);
            if (stmtType == "procedure") {
                //Database::insertProcedure(statement.at(1));
            }
            else if (stmtType == "if" || stmtType == "while") {
                Database::insertStatement(stmtNo, stmtType);

                auto startIt = next(statement.begin(), 2);
                auto endIt = prev(statement.end(), 1);
                if (stmtType == "if") {
                    // remove "then"
                    endIt--;
                }
                std::string conExpression = accumulate(startIt, endIt, std::string{});
                // insert partial info into stack
                stack.push(std::vector<std::string>{stmtType, std::to_string(stmtNo), conExpression});
            }
            else if (stmtType == "else") {
                // insert if_end_stmtNo
                stack.top().push_back(std::to_string(stmtNo - 1));
                // else statement does not accumulate stmtNo
                statement.clear();
                continue;
            }
            else {
                processSingleStmt(statement);
            }
            stmtNo++;
            statement.clear();
        }
        else if (*it == "}" && !stack.empty()) {
            // insert end_stmtNo into stack
            std::vector<std::string> vector = stack.top();
            if (vector.at(0) == "if" && vector.size() > 3) {
                vector.push_back(std::to_string(stmtNo - 1));
                //Database::insertIf(vector);
                stack.pop();
            }
            else if (vector.at(0) == "while") {
                vector.push_back(std::to_string(stmtNo - 1));
                //Database::insertWhile(vector);
                stack.pop();
            }
        }
        else {
            statement.push_back(*it);
        }
    }
}

void SourceProcessor::processSingleStmt(std::vector<std::string> statement) {
    // set to store all variables and constants in order to check duplication
    std::set<std::string> vars;
    std::set<std::string> cons;
    std::string stmtType = statement.at(0);
    if (stmtType == "read") {
        Database::insertStatement(stmtNo, "read");
        // check if variable is declared
        auto itVars = vars.find(statement.at(1));
        if (itVars == vars.end()) { // not declared
            //Database::insertVariable(statement.at(1));
            vars.insert(statement.at(1));
        }
    }
    else if (stmtType == "print") {
        Database::insertStatement(stmtNo, "print");
    }
    else { // assignment, e.g., index = num1, con1 = 10
        Database::insertStatement(stmtNo, "assign");
        auto startIt = next(statement.begin(), 2);
        std::string expression = accumulate(startIt, statement.end(), std::string{});
        Database::insertAssignment(stmtNo, statement.at(0), expression);

        // check if variable is declared
        auto itVars = vars.find(statement.at(0));
        if (itVars == vars.end()) { // not declared
            //Database::insertVariable(statement.at(0));
            vars.insert(statement.at(0));
        }

        // check if RHS is integer
        char c = statement.at(2)[0];
        if (isdigit(c)) { // constant statement
            auto itCons = cons.find(statement.at(2));
            if (itCons == cons.end()) { // not declared
                cons.insert(statement.at(2));
                Database::insertConstant(static_cast<int64_t>(stoul(statement.at(2))));
            }
        }
    }
}
