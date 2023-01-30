#include <string>
#include "SQLiteWrapper.h"

vector<vector<string>> SQLiteWrapper::dbResults;

void SQLiteWrapper::open(const string& database) {
    const int ret = sqlite3_open(database.c_str(), &dbConnection);
    if (ret != SQLITE_OK) {
        throw std::exception("SQLiteWrapper: unable to open database");
    }
    dbResults = vector<vector<string>>();
}

void SQLiteWrapper::close() {
    sqlite3_close(dbConnection);
}

void SQLiteWrapper::execute(const string& sql) {
    char* errorMessage;

    const int ret = sqlite3_exec(dbConnection, sql.c_str(), NULL, 0, &errorMessage);
    if (ret != SQLITE_OK) {
        throw std::exception(("SQLiteWrapper: " + string(errorMessage)).c_str());
    }
}

vector<vector<string>> SQLiteWrapper::select(const string& sql) {
    char* errorMessage;

    // clear the existing results
    dbResults.clear();

    const int ret = sqlite3_exec(dbConnection, sql.c_str(), callback, 0, &errorMessage);
    if (ret != SQLITE_OK) {
        throw std::exception(("SQLiteWrapper: " + string(errorMessage)).c_str());
    }

    return dbResults;
}

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int SQLiteWrapper::callback(void* NotUsed, int argc, char** argv, char** azColName) {
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
