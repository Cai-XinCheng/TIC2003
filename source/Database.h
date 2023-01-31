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
    static void insertConstant(unsigned int constantValue);

    // method to insert a statement into the database
    static void insertStatement(unsigned int statementNo, string type);

    // method to get all the procedures from the database
    static void getProcedures(vector<string>& results);

    // method to get all the variables from the database
    static void getVariables(vector<string>& results);

    // method to get all the constants from the database
    static void getConstants(vector<string>& results);

    // method to get all the statements from the database
    static void getStatements(vector<string>& results);

    // method to get all the statements of the specific type from the database
    static void getStatementsByType(const string& type, vector<string>& results);

private:
    static SQLiteWrapper db;
};

