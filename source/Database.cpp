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
    map<string, string> map;
    map["procedures"] = "CREATE TABLE procedures (procedureName VARCHAR(255) PRIMARY KEY);";
    map["constants"] = "CREATE TABLE constants (value INTEGER PRIMARY KEY);";
    map["variables"] = "CREATE TABLE variables (stmtNo INTEGER PRIMARY KEY, name VARCHAR(255));";
    map["statements"] = "CREATE TABLE statements (stmtNo INTEGER PRIMARY KEY, type VARCHAR(255));";

    for (auto it = map.begin(); it != map.end(); it++) {
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
