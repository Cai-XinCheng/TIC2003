#include <map>
#include "Database.h"

SQLiteWrapper Database::db;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
    // open a database connection and store the pointer into dbConnection
    db.open("database.db");

    // map to store CREATE TABLE queries
    // key: table name; value: query
    map<string, string> createTableSQLs;
    createTableSQLs["procedures"] = "CREATE TABLE procedures (procedureName VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["constants"] = "CREATE TABLE constants (value INTEGER NOT NULL PRIMARY KEY);";
    createTableSQLs["variables"] = "CREATE TABLE variables (name VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["statements"] = "CREATE TABLE statements (stmtNo INTEGER NOT NULL PRIMARY KEY, type VARCHAR(255) NOT NULL);";

    for (auto const& pair : createTableSQLs) {
        // drop the existing table (if any)
        string dropTableSQL = "DROP TABLE IF EXISTS " + pair.first;
        db.execute(dropTableSQL);

        // create table
        string createTableSQL = pair.second;
        db.execute(createTableSQL);
    }
}

// method to close the database connection
void Database::close() {
    db.close();
}

// method to insert a procedure into the database
void Database::insertProcedure(string procedureName) {
    string insertProcedureSQL = "INSERT INTO procedures ('procedureName') VALUES (?);";
    db.execute(insertProcedureSQL, procedureName);
}

// method to insert a variable into the database
void Database::insertVariable(string variableName) {
    string insertVariableSQL = "INSERT INTO variables ('name') VALUES(?);";
    db.execute(insertVariableSQL, variableName);
}

// method to insert a constant into the database
void Database::insertConstant(unsigned int constantValue) {
    string insertConstantSQL = "INSERT INTO constants ('value') VALUES(?);";
    db.execute(insertConstantSQL, constantValue);
}

// method to insert a statement into the database
void Database::insertStatement(unsigned int statementNo, string type) {
    string insertStatementSQL = "INSERT INTO statements ('stmtNo', 'type') VALUES(?, ?);";
    db.execute(insertStatementSQL, statementNo, type);
}

// method to get all the procedures from the database
void Database::getProcedures(vector<string>& results) {
    // retrieve the procedures from the procedure table
    // The callback method is only used when there are results to be returned.
    string getProceduresSQL = "SELECT * FROM procedures;";
    vector<vector<string>> dbResults = db.select(getProceduresSQL);

    // postprocess the results from the database so that the output is just a vector of procedure names
    filterByColumnIndex(dbResults, results, 0);
}

// method to get all the variable from the database
void Database::getVariables(vector<string>& results) {
    // retrieve the variables from the constants table
    // The callback method is only used when there are results to be returned.
    string getVariablesSQL = "SELECT name FROM variables;";
    vector<vector<string>> dbResults = db.select(getVariablesSQL);

    // postprocess the results from the database so that the output is just a vector of variable names
    filterByColumnIndex(dbResults, results, 0);
}

// method to get all the procedures from the database
void Database::getConstants(vector<string>& results) {
    // retrieve the constants from the constants table
    // The callback method is only used when there are results to be returned.
    string getConstantsSQL = "SELECT value FROM constants;";
    vector<vector<string>> dbResults = db.select(getConstantsSQL);

    // postprocess the results from the database so that the output is just a vector of constant values
    filterByColumnIndex(dbResults, results, 0);
}

// method to get all the statements from the database
void Database::getStatements(vector<string>& results) {
    // retrieve the statements from the constants table
    // The callback method is only used when there are results to be returned.
    string getStatementsSQL = "SELECT stmtNo FROM statements;";
    vector<vector<string>> dbResults = db.select(getStatementsSQL);

    // postprocess the results from the database so that the output is just a vector of statement number
    filterByColumnIndex(dbResults, results, 0);
}

// method to get all the statements of the specific type from the database
void Database::getStatementsByType(const string& type, vector<string>& results) {
    // retrieve the statements from the constants table
    // The callback method is only used when there are results to be returned.
    string getStatementsSQL = "SELECT stmtNo FROM statements where type = ?;";
    vector<vector<string>> dbResults = db.select(getStatementsSQL, type);;

    // postprocess the results from the database so that the output is just a vector of statement number
    filterByColumnIndex(dbResults, results, 0);
}

// method to filter input and fill into output by the column index
void Database::filterByColumnIndex(const vector<vector<string>>& input, vector<string>& output, int columnIndex) {
    for (vector<string> dbRow : input) {
        output.push_back(dbRow.at(columnIndex));
    }
}
