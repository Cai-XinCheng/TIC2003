#include "Database.h"

sqlite3* Database::dbConnection;
vector<vector<string>> Database::dbResults;
char* Database::errorMessage;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
	// open a database connection and store the pointer into dbConnection
	sqlite3_open("database.db", &dbConnection);

	// map to store CREATE TABLE queries
	// key: table name; value: query
	map<string, string> createTableSQLs;
    createTableSQLs["procedures"] = "CREATE TABLE procedures (procedureName VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["constants"] = "CREATE TABLE constants (value INTEGER NOT NULL PRIMARY KEY);";
    createTableSQLs["variables"] = "CREATE TABLE variables (name VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["statements"] = "CREATE TABLE statements (stmtNo INTEGER NOT NULL PRIMARY KEY, type NOT NULL VARCHAR(255));";

	for (auto it = createTableSQLs.begin(); it != createTableSQLs.end(); it++) {
		// result of sqlite3_exe()
		int execResult = 0;

		// drop the existing table (if any)
		string dropTableSQL = "DROP TABLE IF EXISTS " + it->first;
		execResult = sqlite3_exec(dbConnection, dropTableSQL.c_str(), NULL, 0, &errorMessage);
		checkSqlExecResult(execResult, errorMessage);

		// create table
		string createTableSQL = it->second;
		execResult = sqlite3_exec(dbConnection, createTableSQL.c_str(), NULL, 0, &errorMessage);
		checkSqlExecResult(execResult, errorMessage);
	}

	// initialize the result vector
	dbResults = vector<vector<string>>();
}

// method to close the database connection
void Database::close() {
	sqlite3_close(dbConnection);
}

// method to insert a procedure into the database
void Database::insertProcedure(string procedureName) {
	string insertProcedureSQL = "INSERT INTO procedures ('procedureName') VALUES ('" + procedureName + "');";
	sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

// method to insert a variable into the database
void Database::insertVariable(string variableName) {
	string insertVariableSQL = "INSERT INTO variables ('name') VALUES('" + variableName + "');";
	sqlite3_exec(dbConnection, insertVariableSQL.c_str(), NULL, 0, &errorMessage);
}

// method to insert a constant into the database
void Database::insertConstant(unsigned int constantValue) {
    string insertConstantSQL = "INSERT INTO constants ('value') VALUES(" + std::to_string(constantValue) + ");";
    sqlite3_exec(dbConnection, insertConstantSQL.c_str(), NULL, 0, &errorMessage);
}

// method to insert a statement into the database
void Database::insertStatement(unsigned int statementNo, string type) {
	string insertStatementSQL = "INSERT INTO statements ('stmtNo', 'type') VALUES(" + std::to_string(statementNo) + ", '" + type + "');";
	sqlite3_exec(dbConnection, insertStatementSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the procedures from the database
void Database::getProcedures(vector<string>& results){
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getProceduresSQL = "SELECT * FROM procedures;";
	sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

// method to get all the variable from the database
void Database::getVariables(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the variables from the constants table
    // The callback method is only used when there are results to be returned.
    string getVariablesSQL = "SELECT name FROM variables;";
    sqlite3_exec(dbConnection, getVariablesSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of variable names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the procedures from the database
void Database::getConstants(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the constants from the constants table
    // The callback method is only used when there are results to be returned.
    string getConstantsSQL = "SELECT value FROM constants;";
    sqlite3_exec(dbConnection, getConstantsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of constant values
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the statements from the database
void Database::getStatements(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the statements from the constants table
    // The callback method is only used when there are results to be returned.
    string getStatementsSQL = "SELECT stmtNo FROM statements;";
    sqlite3_exec(dbConnection, getStatementsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of statement number
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the statements of the specific type from the database
void Database::getStatementsByType(const string& type, vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the statements from the constants table
    // The callback method is only used when there are results to be returned.
    string getStatementsSQL = "SELECT stmtNo FROM statements where type='" + type + "';";
    sqlite3_exec(dbConnection, getStatementsSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of statement number
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	NotUsed = 0;
	vector<string> dbRow;

	// argc is the number of columns for this row of results
	// argv contains the values for the columns
	// Each value is pushed into a vector.
	for (int i = 0; i < argc; i++) {
		dbRow.push_back(argv[i]);
	}

	// The row is pushed to the vector for storing all rows of results 
	dbResults.push_back(dbRow);

	return 0;
}

// check SQL query execution result, print error message if any
void Database::checkSqlExecResult(int execResult, char* errMessage) {
	if (execResult != SQLITE_OK) {
		printf("**********SQL Error: %s \n", errMessage);
	}
}
