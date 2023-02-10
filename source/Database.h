#pragma once

#include "SQLiteWrapper.h"

using namespace std;

// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class Database {
public:
    // method to connect to the database and initialize tables in the database
    static void initialize();

    // method to close the database connection
    static void close();

    // method to insert a procedure into the database
    static void insertProcedure(string procedureName);

    // method to insert a variable into the database
    static void insertVariable(string variableName);

    // method to insert a constant into the database
    static void insertConstant(int64_t constantValue);

    // method to insert a statement into the database
    static void insertStatement(uint32_t statementNo, string type);

    // method to insert a if into the database
    static void insertIf(uint32_t conStmtNo, uint32_t ifStmtNo, uint32_t elseStmtNo);

    // method to insert a while into the database
    static void insertWhile(uint32_t conStmtNo, uint32_t endStmtNo);

    // method to get all the procedures from the database
    static void getProcedures(vector<string>& results);

    // method to get all the variables from the database
    static void getVariables(vector<string>& results);

    // method to get all the constants from the database
    static void getConstants(vector<int64_t>& results);

    // method to get all the statements from the database
    static void getStatements(vector<uint32_t>& results);

    // method to get all the statements of the specific type from the database
    static void getStatementsByType(const string& type, vector<uint32_t>& results);

private:
    // the instance of SQLiteWrapper
    static SQLiteWrapper db;
};

