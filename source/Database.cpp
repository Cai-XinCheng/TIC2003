#include "Database.h"
#include <map>
#include <format>

SQLiteWrapper Database::db;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
    // open a database connection and store the pointer into dbConnection
    db.open("database.db");

    // map to store CREATE TABLE queries
    // key: table name; value: query
    std::map<std::string, std::string, std::less<>> createTableSQLs;
    createTableSQLs["procedures"] = "CREATE TABLE procedures (procedureName VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["variables"] = "CREATE TABLE variables (name VARCHAR(255) NOT NULL, stmtNo INTEGER NOT NULL, relation VARCHAR(255) NOT NULL, procedureName VARCHAR(255) NOT NULL, PRIMARY KEY (name, stmtNo, relation));";
    createTableSQLs["constants"] = "CREATE TABLE constants (value INTEGER NOT NULL PRIMARY KEY);";
    createTableSQLs["statements"] = "CREATE TABLE statements (stmtNo INTEGER NOT NULL PRIMARY KEY, type VARCHAR(255) NOT NULL);";
    createTableSQLs["assignments"] = "CREATE TABLE assignments (stmtNo INTEGER NOT NULL PRIMARY KEY, variable VARCAHR(255) NOT NULL, expression VARCHAR(255) NOT NULL);";
    createTableSQLs["nexts"] = "CREATE TABLE nexts (stmtNo INTEGER NOT NULL, nextStmtNo INTEGER NOT NULL, PRIMARY KEY (stmtNo, nextStmtNo));";
    createTableSQLs["parents"] = "CREATE TABLE parents (stmtNo INTEGER NOT NULL PRIMARY KEY, parentStmtNo INTEGER NOT NULL);";
    createTableSQLs["calls"] = "CREATE TABLE calls (stmtNo INTEGER NOT NULL PRIMARY KEY, procedureName VARCHAR(255) NOT NULL);";

    for (const auto& [tableName, createTableSQL] : createTableSQLs) {
        // drop the existing table (if any)
        std::string dropTableSQL = std::format("DROP TABLE IF EXISTS {};", tableName);
        db.execute(dropTableSQL);

        // create table
        db.execute(createTableSQL);
    }
}

// method to close the database connection
void Database::close() {
    db.close();
}

// insert functions
// method to insert a procedure into the database
void Database::insertProcedure(std::string procedureName) {
    std::string insertProcedureSQL = "INSERT INTO procedures ('procedureName') VALUES (?);";
    db.execute(insertProcedureSQL, procedureName);
}

// method to insert a variable into the database
void Database::insertVariable(std::string variableName, uint32_t stmtNo, std::string relation, std::string procedureName) {
    std::string insertVariableSQL = "INSERT INTO variables ('name', 'stmtNo', 'relation', 'procedureName') VALUES(?, ?, ?, ?);";
    db.execute(insertVariableSQL, variableName, stmtNo, relation, procedureName);
}

// method to insert a constant into the database
void Database::insertConstant(int64_t constantValue) {
    std::string insertConstantSQL = "INSERT INTO constants ('value') VALUES(?);";
    db.execute(insertConstantSQL, constantValue);
}

// method to insert a statement into the database
void Database::insertStatement(uint32_t stmtNo, std::string type) {
    std::string insertStatementSQL = "INSERT INTO statements ('stmtNo', 'type') VALUES(?, ?);";
    db.execute(insertStatementSQL, stmtNo, type);
}

// method to insert a assignment into the database
void Database::insertAssignment(uint32_t stmtNo, std::string variable, std::string expression) {
    std::string insertStatementSQL = "INSERT INTO assignments ('stmtNo', 'variable', 'expression') VALUES(?, ?, ?);";
    db.execute(insertStatementSQL, stmtNo, variable, expression);
}

// method to insert a next into the database
void Database::insertNext(uint32_t stmtNo, uint32_t nextStmtNo) {
    std::string insertStatementSQL = "INSERT INTO nexts ('stmtNo', 'nextStmtNo') VALUES(?, ?)";
    db.execute(insertStatementSQL, stmtNo, nextStmtNo);
}

// method to insert a parent into the database
void Database::insertParent(uint32_t stmtNo, uint32_t parentStmtNo) {
    std::string insertStatementSQL = "INSERT INTO parents ('stmtNo', 'parentStmtNo') VALUES(?, ?)";
    db.execute(insertStatementSQL, stmtNo, parentStmtNo);
}

// method to insert a parent into the database
void Database::insertCall(uint32_t stmtNo, std::string procedureName) {
    std::string insertStatementSQL = "INSERT INTO calls ('stmtNo', 'procedureName') VALUES(?, ?)";
    db.execute(insertStatementSQL, stmtNo, procedureName);
}

// method to get data from the database
void Database::select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql) {
    db.select(dbResults, sql);
}
