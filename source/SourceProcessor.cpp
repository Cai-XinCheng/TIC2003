#include "SourceProcessor.h"
#include<set>
#include<stack>
#include <numeric>

void insertNext(unsigned int i, std::vector<std::string> tokens);
std::string readExpression(unsigned int& i, std::vector<std::string> tokens, std::string procedureName);
std::string normalize(std::string expression);

// statement number
uint32_t stmtNo = 0;

// set to store all variables and constants in order to check duplication
std::set<std::string> vars;
std::set<std::string> cons;

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

    /*
    // Debug, print out tokens
    printf("-------------------------------\n");
    for (auto const& string : tokens) {
        printf("%s\n", string.c_str());
    }
    printf("-------------------------------\n");
    */

    //processToken(tokens);

    // stack to store current parent statement number
    std::stack<uint32_t> parent;
    std::string procedureName;

    unsigned int i = 0;
    while (i < tokens.size()) {
        std::string token = tokens.at(i);
        if (token == "procedure") {
            i++; // procedure name
            procedureName = tokens.at(i);
            Database::insertProcedure(procedureName);
            i++; // "{"
            stmtNo++;
        }
        else if (token == "read") {
            i++; // variable

            if (!parent.empty()) {
                Database::insertParent(stmtNo, parent.top());
            }
            Database::insertStatement(stmtNo, "read");
            Database::insertVariable(tokens.at(i), stmtNo, "modify", procedureName);

            i++; // ";"
            insertNext(i, tokens);
            stmtNo++;
        }
        else if (token == "print") {
            i++; // variable

            if (!parent.empty()) {
                Database::insertParent(stmtNo, parent.top());
            }
            Database::insertStatement(stmtNo, "print");
            Database::insertVariable(tokens.at(i), stmtNo, "use", procedureName);

            i++; // ";"
            insertNext(i, tokens);
            stmtNo++;
        }
        else if (token == "while" || token == "if") {
            if (!parent.empty()) {
                Database::insertParent(stmtNo, parent.top());
            }
            parent.push(stmtNo);
            i++; // "("
            // loop condition expression
            readExpression(i, tokens, procedureName);
            i++; // "{"
            insertNext(i, tokens);
            stmtNo++;
        }
        else if (token == "}") {
            if (i != tokens.size() - 1) {
                if (tokens.at(i + 1) == "else") {
                    Database::insertNext(parent.top(), stmtNo);
                    i += 2;
                }
                else if (tokens.at(i + 1) == "procedure") {
                    parent.pop();
                }
                else {
                    Database::insertNext(parent.top(), stmtNo);
                    parent.pop();
                }
                i++;
            }
            else {
                break;
            }
            
        }
        else if (token == "{" || token == ";") {
            i++;
        }
        else { // assignment 
            Database::insertStatement(stmtNo, "assign");

            if (!parent.empty()) {
                Database::insertParent(stmtNo, parent.top());
            }

            // check if variable is declared
            std::string variableName = tokens.at(i);
            auto itVars = vars.find(variableName);
            if (itVars == vars.end()) { // not declared
                Database::insertVariable(variableName, stmtNo, "modify", procedureName);
                vars.insert(variableName);
            }
            i++; // "="
            i++; // RHS

            // loop RHS
            std::string expression = readExpression(i, tokens, procedureName);
            
            // normalize expression
            std::string normalizedExpression = normalize(expression);

            Database::insertAssignment(stmtNo, variableName, normalizedExpression);
            i++;
            if (i != token.size() - 1) { // not last statement
                Database::insertNext(stmtNo, stmtNo + 1);
            }
            stmtNo++;
        }
    }
}

// Only works without multiple procedure !!!
void insertNext(unsigned int i, std::vector<std::string> tokens) {
    if (i != tokens.size() - 1) { // not last statement
        Database::insertNext(stmtNo, stmtNo + 1);
    }
}

std::string readExpression(unsigned int& i, std::vector<std::string> tokens, std::string procedureName) {
    std::string expression = "";
    while (i < tokens.size()) {
        if (tokens.at(i) == ";" || tokens.at(i + 1) == "{") {
            break;
        }
        std::string str = tokens.at(i);
        // a constant
        if (isdigit(str[0])) {
            auto itCons = cons.find(str);
            if (itCons == cons.end()) { // not declared
                cons.insert(str);
                Database::insertConstant(static_cast<int64_t>(stoul(str)));
            }
        } // a variable
        else if (isalpha(str[0])) {
            auto itVars = vars.find(str);
            if (itVars == vars.end()) { // not declared
                vars.insert(str);
                Database::insertVariable(str, stmtNo, "use", procedureName);
            }
        }
        expression += str;
        i++;
    }
    vars.clear();
    return expression;
}

std::string normalize(std::string expression) {
    return expression;
}
