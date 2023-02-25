#include "Database.h"
#include <map>

SQLiteWrapper Database::db;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
    // open a database connection and store the pointer into dbConnection
    db.open("database.db");

    // map to store CREATE TABLE queries
    // key: table name; value: query
    std::map<std::string, std::string, std::less<>> createTableSQLs;
    createTableSQLs["procedures"] = "CREATE TABLE procedures (procedureName VARCHAR(255) NOT NULL PRIMARY KEY);";
    createTableSQLs["constants"] = "CREATE TABLE constants (value INTEGER NOT NULL PRIMARY KEY);";
    createTableSQLs["variables"] = "CREATE TABLE variables (name VARCHAR(255) NOT NULL, stmtNo INTEGER NOT NULL, PRIMARY KEY(name, stmtNo));";
    createTableSQLs["statements"] = "CREATE TABLE statements (stmtNo INTEGER NOT NULL PRIMARY KEY, type VARCHAR(255) NOT NULL);";
    createTableSQLs["ifs"] = "CREATE TABLE ifs (stmtNo INTEGER NOT NULL PRIMARY KEY, expression VARCHAR(255) NOT NULL);";
    createTableSQLs["whiles"] = "CREATE TABLE whiles (stmtNo INTEGER NOT NULL PRIMARY KEY, expression VARCHAR(255) NOT NULL);";
    createTableSQLs["assignments"] = "CREATE TABLE assignments (stmtNo INTEGER NOT NULL PRIMARY KEY, variable VARCAHR(255) NOT NULL, expression VARCHAR(255) NOT NULL);";
    createTableSQLs["nexts"] = "CREATE TABLE nexts (stmtNo INTEGER NOT NULL PRIMARY KEY, next_stmtNo INTEGER NOT NULL)";
    createTableSQLs["parents"] = "CREATE TABLE parents (stmtNo INTEGER NOT NULL PRIMARY KEY, parent_stmtNo INTEGER NOT NULL)";
    //createTableSQLs["calls"] = "CREATE TABLE calls (procedureName VARCHAR(255) NOT NULL, calleeName VARCHAR(255) NOT NULL, PRIMARY KEY(procedureName, calleeName))";

    for (auto const& pair : createTableSQLs) {
        // drop the existing table (if any)
        std::string dropTableSQL = "DROP TABLE IF EXISTS " + pair.first + ";";
        db.execute(dropTableSQL);

        // create table
        std::string createTableSQL = pair.second;
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
void Database::insertVariable(std::string variableName) {
    std::string insertVariableSQL = "INSERT INTO variables ('name') VALUES(?);";
    db.execute(insertVariableSQL, variableName);
}

// method to insert a constant into the database
void Database::insertConstant(int64_t constantValue) {
    std::string insertConstantSQL = "INSERT INTO constants ('value') VALUES(?);";
    db.execute(insertConstantSQL, constantValue);
}

// method to insert a statement into the database
void Database::insertStatement(uint32_t statementNo, std::string type) {
    std::string insertStatementSQL = "INSERT INTO statements ('stmtNo', 'type') VALUES(?, ?);";
    db.execute(insertStatementSQL, statementNo, type);
}

// method to insert a if into the database
void Database::insertIf(std::vector<std::string> vector) {
    std::string insertStatementSQL = "INSERT INTO ifs ('con_stmtNo', 'expression', 'if_end_stmtNo', 'else_end_stmtNo') VALUES(?, ?, ?, ?);";
    db.execute(insertStatementSQL, static_cast<uint32_t>(stoul(vector.at(1))), vector.at(2), static_cast<uint32_t>(stoul(vector.at(3))), static_cast<uint32_t>(stoul(vector.at(4))));
}

// method to insert a while into the database
void Database::insertWhile(std::vector<std::string> vector) {
    std::string insertStatementSQL = "INSERT INTO whiles ('con_stmtNo','expression', 'end_stmtNo') VALUES(?, ?, ?);";
    db.execute(insertStatementSQL, static_cast<uint32_t>(stoul(vector.at(1))), vector.at(2), static_cast<uint32_t>(stoul(vector.at(3))));
}

// method to insert a assignment into the database
void Database::insertAssignment(uint32_t stmtNo, std::string variable, std::string expression) {
    std::string insertStatementSQL = "INSERT INTO assignments ('stmtNo', 'variable', 'expression') VALUES(?, ?, ?);";
    db.execute(insertStatementSQL, stmtNo, variable, expression);
}


// get functions
// method to get all the procedures from the database
void Database::getProcedures(std::vector<std::string>& results) {
    // retrieve the procedures from the procedure table
    std::string getProceduresSQL = "SELECT procedureName FROM procedures;";
    db.selectFirstColumn<std::string>(results, getProceduresSQL);
}

// method to get all the variable from the database
void Database::getVariables(std::vector<std::string>& results) {
    // retrieve the variables from the constants table
    std::string getVariablesSQL = "SELECT name FROM variables;";
    db.selectFirstColumn<std::string>(results, getVariablesSQL);
}

// method to get all the procedures from the database
void Database::getConstants(std::vector<int64_t>& results) {
    // retrieve the constants from the constants table
    std::string getConstantsSQL = "SELECT value FROM constants;";
    db.selectFirstColumn<int64_t>(results, getConstantsSQL);
}

// method to get all the statements from the database
void Database::getStatements(std::vector<uint32_t>& results) {
    // retrieve the statements from the constants table
    std::string getStatementsSQL = "SELECT stmtNo FROM statements;";
    db.selectFirstColumn<uint32_t>(results, getStatementsSQL);
}

// method to get all the statements of the specific type from the database
void Database::getStatementsByType(const std::string& type, std::vector<uint32_t>& results) {
    // retrieve the statements from the constants table
    std::string getStatementsSQL = "SELECT stmtNo FROM statements where type = ?;";
    db.selectFirstColumn<uint32_t>(results, getStatementsSQL, type);
}
