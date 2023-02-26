#include "QueryProcessor.h"
#include "Tokenizer.h"
#include "PQLParser.h"
#include "PQL2SQLTransformer.h"
#include <numeric>

// constructor
QueryProcessor::QueryProcessor() {}

// destructor
QueryProcessor::~QueryProcessor() {}

// method to evaluate a query
// This method currently only handles queries for getting all the procedure names,
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all required queries.
void QueryProcessor::evaluate(std::string query, std::vector<std::string>& output) {
    // clear the output vector
    output.clear();

    // tokenize the query
    Tokenizer tk;
    std::vector<std::string> tokens;
    tk.tokenize(query, tokens);

    // parse the AST
    PQLParser parser;
    SelectClause selectClause = parser.parse(tokens);

    // transform the AST to SQL
    PQL2SQLTransformer transformer;
    std::string sql = transformer.transform(selectClause);

    // retrieve the results from database
    std::vector<std::vector<std::string>> dbResults;
    Database::select(dbResults, sql);

    // post process the results to fill in the output vector
    for (std::vector<std::string> const& row : dbResults) {
        std::string item = std::accumulate(row.begin(), row.end(), std::string(),
            [](std::string const& acc, auto const& element) {
                return !acc.empty() ? acc + " " + element : element;
            });
        output.push_back(item);
    }
}
