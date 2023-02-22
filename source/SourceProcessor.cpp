#include "SourceProcessor.h"
#include<set>
#include<stack>
#include <numeric>


// statement number
uint32_t stmtNo = 0;
// set to store all variables and constants in order to check duplication
set<string> vars;
set<string> cons;

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(string program) {
	// initialize the database
	Database::initialize();

	// tokenize the program
	Tokenizer tk;
    vector<string> tokens;
	tk.tokenize(program, tokens);

    // a vector to store each line of statement
    vector<string> statement;

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

void SourceProcessor::processToken(vector<string> token) {
    vector<string> statement;
    // a stack to store if/while information
    stack<vector<string>> stack;
    for (auto it = token.begin(); it != token.end(); it++) {
        if (*it == ";" || *it == "{") { // end of a statement
            string stmtType = statement.at(0);
            if (stmtType == "procedure") {
                Database::insertProcedure(statement.at(1));
            }
            else if (stmtType == "if" || stmtType == "while") {
                Database::insertStatement(stmtNo, stmtType);

                auto startIt = next(statement.begin(), 2);
                auto endIt = prev(statement.end(), 1);
                if (stmtType == "if") {
                    // remove "then"
                    endIt--;
                }
                string conExpression = accumulate(startIt, endIt, string{});
                // insert partial info into stack
                stack.push(vector<string>{stmtType, to_string(stmtNo), conExpression});
            }
            else if (stmtType == "else") {
                // insert if_end_stmtNo
                stack.top().push_back(to_string(stmtNo - 1));
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
            vector<string> vector = stack.top();
            if (vector.at(0) == "if" && vector.size() > 3) {
                vector.push_back(to_string(stmtNo - 1));
                Database::insertIf(vector);
                stack.pop();
            }
            else if (vector.at(0) == "while") {
                vector.push_back(to_string(stmtNo - 1));
                Database::insertWhile(vector);
                stack.pop();
            }
        }
        else {
            statement.push_back(*it);
        }
    }
}

void SourceProcessor::processSingleStmt(vector<string> statement) {
    string stmtType = statement.at(0);
    if (stmtType == "read") {
        Database::insertStatement(stmtNo, "read");
        // check if variable is declared
        auto itVars = vars.find(statement.at(1));
        if (itVars == vars.end()) { // not declared
            Database::insertVariable(statement.at(1));
            vars.insert(statement.at(1));
        }
    }
    else if (stmtType == "print") {
        Database::insertStatement(stmtNo, "print");
    }
    else { // assignment, e.g., index = num1, con1 = 10
        Database::insertStatement(stmtNo, "assign");
        auto startIt = next(statement.begin(), 2);
        string expression = accumulate(startIt, statement.end(), string{});
        Database::insertAssignment(stmtNo, statement.at(0), expression);

        // check if variable is declared
        auto itVars = vars.find(statement.at(0));
        if (itVars == vars.end()) { // not declared
            Database::insertVariable(statement.at(0));
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
