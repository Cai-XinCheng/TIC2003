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

    // method to insert a procedure into the database
    static void insertProcedure(std::string procedureName);

    // method to insert a variable into the database
    static void insertVariable(std::string variableName, uint32_t stmtNo);

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
    static void insertCall(uint32_t stmtNo, uint32_t calleeStmtNo);

    // method to get data from the database
    static void select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql);

private:
    // the instance of SQLiteWrapper
    static SQLiteWrapper db;
};

