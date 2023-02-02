#include "QueryProcessor.h"
#include "Tokenizer.h"

// constructor
QueryProcessor::QueryProcessor() {}

// destructor
QueryProcessor::~QueryProcessor() {}

// method to evaluate a query
// This method currently only handles queries for getting all the procedure names,
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all required queries.
void QueryProcessor::evaluate(string query, vector<string>& output) {
    // clear the output vector
    output.clear();

    // tokenize the query
    Tokenizer tk;
    vector<string> tokens;
    tk.tokenize(query, tokens);

    // check what type of synonym is being declared
    string synonymType = tokens.at(0);

    if (synonymType == "procedure") {
        // create a vector for storing the results from database
        vector<string> databaseResults;

        // call the method in database to retrieve the results
        // This logic is highly simplified based on iteration 1 requirements and 
        // the assumption that the queries are valid.
        Database::getProcedures(databaseResults);

        // post process the results to fill in the output vector
        for (string databaseResult : databaseResults) {
            output.push_back(databaseResult);
        }
    }
    else if (synonymType == "variable") {
        // create a vector for storing the results from database
        vector<string> databaseResults;

        // call the method in database to retrieve the results
        // This logic is highly simplified based on iteration 1 requirements and 
        // the assumption that the queries are valid.
        Database::getVariables(databaseResults);

        // post process the results to fill in the output vector
        for (string databaseResult : databaseResults) {
            output.push_back(databaseResult);
        }
    }
    else if (synonymType == "constant") {
        // create a vector for storing the results from database
        vector<uint32_t> databaseResults;

        // call the method in database to retrieve the results
        // This logic is highly simplified based on iteration 1 requirements and 
        // the assumption that the queries are valid.
        Database::getConstants(databaseResults);

        // post process the results to fill in the output vector
        for (uint32_t databaseResult : databaseResults) {
            output.push_back(to_string(databaseResult));
        }
    }
    else if (synonymType == "assign" || synonymType == "print" || synonymType == "read") {
        // create a vector for storing the results from database
        vector<uint32_t> databaseResults;

        // call the method in database to retrieve the results
        // This logic is highly simplified based on iteration 1 requirements and 
        // the assumption that the queries are valid.
        Database::getStatementsByType(synonymType, databaseResults);

        // post process the results to fill in the output vector
        for (uint32_t databaseResult : databaseResults) {
            output.push_back(to_string(databaseResult));
        }
    }
    else if (synonymType == "stmt") {
        // create a vector for storing the results from database
        vector<uint32_t> databaseResults;

        // call the method in database to retrieve the results
        // This logic is highly simplified based on iteration 1 requirements and 
        // the assumption that the queries are valid.
        Database::getStatements(databaseResults);

        // post process the results to fill in the output vector
        for (uint32_t databaseResult : databaseResults) {
            output.push_back(to_string(databaseResult));
        }
    }
}
