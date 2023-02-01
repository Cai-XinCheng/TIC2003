#include "SourceProcessor.h"
#include<set>

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

    // logic to parse program for Iteration 1
    // statement number
    int stmtNo = 1;

    // insert the procedure into the database
    Database::insertProcedure(tokens.at(1));
   
    vector<string> statement;
    // set to store all variables and constants in order to check duplication
    set<string> vars;
    set<string> cons;
    // iterate tokens from 3th element(first statement)
    auto it = tokens.begin();
    for (advance(it, 3); it != tokens.end(); it++) {
        if (*it != "}" && *it != ";") { 
            statement.push_back(*it);
        }
        else if (statement.size() > 0) { // end of a statement
            if (statement.at(0) == "read") {
                Database::insertStatement(stmtNo, "read");
                Database::insertVariable(statement.at(1));
                vars.insert(statement.at(1));
            }
            else if (statement.at(0) == "print") {
                Database::insertStatement(stmtNo, "print");
            }
            else { // assignment, e.g., index = num1, con1 = 10
                Database::insertStatement(stmtNo, "assign");

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
                        Database::insertConstant(atoi(statement.at(2).c_str()));
                    }
                }
            }
            stmtNo++;
            statement.clear();
        }
    }
}
