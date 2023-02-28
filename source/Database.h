#pragma once

#include <string>
#include <vector>
#include "SQLiteWrapper.h"

// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class Database {
public:
    // method to connect to the database and initialize tables in the database
    static void initialize();

    // method to close the database connection
    static void close();

    // sqlite3 user function to check whether a statement is a parent of another statement
    static void sqlite3_check_parent(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a statement is a parent (directly or indirectly) of another statement
    static void sqlite3_check_parent_t(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a statement is a next of another statement
    static void sqlite3_check_next(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a statement is a next (directly or indirectly) of another statement
    static void sqlite3_check_next_t(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a specified object calls a specified variable or any variable
    static void sqlite3_check_call(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a specified object calls (directly or indirectly) a specified variable or any variable
    static void sqlite3_check_call_t(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a specified object modifies a specified variable or any variable
    static void sqlite3_check_modify(sqlite3_context* context, int argc, sqlite3_value** argv);

    // sqlite3 user function to check whether a specified object uses a specified variable or any variable
    static void sqlite3_check_use(sqlite3_context* context, int argc, sqlite3_value** argv);

    // method to insert a procedure into the database
    static void insertProcedure(std::string procedureName);

    // method to insert a variable into the database
    static void insertVariable(std::string variableName, uint32_t stmtNo, std::string relation, std::string procedureName);

    // method to insert a constant into the database
    static void insertConstant(int64_t constantValue);

    // method to insert a statement into the database
    static void insertStatement(uint32_t stmtNo, std::string type);

    // method to insert a assignment into the database
    static void insertAssignment(uint32_t stmtNo, std::string variable, std::string expression);

    // method to insert a next into the database
    static void insertNext(uint32_t stmtNo, uint32_t nextStmtNo);

    // method to insert a parent into the database
    static void insertParent(uint32_t stmtNo, uint32_t parentStmtNo);

    // method to insert a parent into the database
    static void insertCall(uint32_t stmtNo, std::string callerName, std::string calleeName);

    // method to get data from the database
    static void select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql);

private:
    // the instance of SQLiteWrapper
    static SQLiteWrapper db;

    // sqlite3 user function to check whether a specified object modifies or uses a specified variable or any variable
    static void check_modify_or_use(const char* functionName, const char* relation, sqlite3_context* context, int argc, sqlite3_value** argv);
};

