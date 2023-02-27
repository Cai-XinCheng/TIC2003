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
    createTableSQLs["calls"] = "CREATE TABLE calls (stmtNo INTEGER NOT NULL PRIMARY KEY, callerName VARCHAR(255) NOT NULL, calleeName VARCHAR(255) NOT NULL);";

    for (const auto& [tableName, createTableSQL] : createTableSQLs) {
        // drop the existing table (if any)
        std::string dropTableSQL = std::format("DROP TABLE IF EXISTS {};", tableName);
        db.execute(dropTableSQL);

        // create table
        db.execute(createTableSQL);
    }

    // create user functions
    db.createFunction("check_parent", 2, SQLITE_ANY, nullptr, &sqlite3_check_parent);
    db.createFunction("check_parent_t", 2, SQLITE_ANY, nullptr, &sqlite3_check_parent_t);
    db.createFunction("check_next", 2, SQLITE_ANY, nullptr, &sqlite3_check_next);
    db.createFunction("check_next_t", 2, SQLITE_ANY, nullptr, &sqlite3_check_next_t);
    db.createFunction("check_modify", -1, SQLITE_ANY, nullptr, &sqlite3_check_modify);
}

// method to close the database connection
void Database::close() {
    db.close();
}

// sqlite3 user function to check whether a statement is a parent of another statement
void Database::sqlite3_check_parent(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_parent", -1);
        return;
    }
    if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER || sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
        sqlite3_result_error(context, "invalid argument type of check_parent", -1);
        return;
    }

    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

    std::string sql = "SELECT 1 FROM parents WHERE stmtNo = ? AND parentStmtNo = ? LIMIT 1;";
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, parentStmtNo);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
}

// sqlite3 user function to check whether a statement is a parent (directly or indirectly) of another statement
void Database::sqlite3_check_parent_t(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_parent_t", -1);
        return;
    }
    if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER || sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
        sqlite3_result_error(context, "invalid argument type of check_parent_t", -1);
        return;
    }

    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

    std::string sql = R"(
        WITH RECURSIVE parents_t AS (
            SELECT stmtNo, parentStmtNo FROM parents WHERE stmtNo = ?
            UNION ALL
            SELECT p.stmtNo, p.parentStmtNo FROM parents AS p
            INNER JOIN parents_t AS pt ON pt.parentStmtNo = p.stmtNo
            WHERE pt.parentStmtNo != ?
        )
        SELECT 1 FROM parents_t WHERE parentStmtNo = ? LIMIT 1;
    )";
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, parentStmtNo, parentStmtNo);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
}

// sqlite3 user function to check whether a statement is a next of another statement
void Database::sqlite3_check_next(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_next", -1);
        return;
    }
    if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER || sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
        sqlite3_result_error(context, "invalid argument type of check_next", -1);
        return;
    }

    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

    std::string sql = "SELECT 1 FROM nexts WHERE stmtNo = ? AND nextStmtNo = ? LIMIT 1;";
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, parentStmtNo);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
}

// sqlite3 user function to check whether a statement is a next (directly or indirectly) of another statement
void Database::sqlite3_check_next_t(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_next_t", -1);
        return;
    }
    if (sqlite3_value_type(argv[0]) != SQLITE_INTEGER || sqlite3_value_type(argv[1]) != SQLITE_INTEGER) {
        sqlite3_result_error(context, "invalid argument type of check_next_t", -1);
        return;
    }

    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

    std::string sql = R"(
        WITH RECURSIVE nexts_t AS (
            SELECT stmtNo, nextStmtNo FROM nexts WHERE stmtNo = ?
            UNION ALL
            SELECT n.stmtNo, n.nextStmtNo FROM nexts AS n
            INNER JOIN nexts_t AS nt ON nt.nextStmtNo = n.stmtNo
            WHERE nt.nextStmtNo != ?
        )
        SELECT 1 FROM nexts_t WHERE nextStmtNo = ? LIMIT 1;
    )";
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, parentStmtNo, parentStmtNo);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
}

// sqlite3 user function to check whether a specified object modifies a specified variable or any variable
void Database::sqlite3_check_modify(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 1 && argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_modify", -1);
        return;
    }

    int arg0Type = sqlite3_value_type(argv[0]);
    if ((arg0Type != SQLITE_INTEGER && arg0Type != SQLITE_TEXT) || (argc == 2 && sqlite3_value_type(argv[1]) != SQLITE_TEXT)) {
        sqlite3_result_error(context, "invalid argument type of check_modify", -1);
        return;
    }

    std::string variableName = argc == 2 ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[1]))) : "";
    std::string sql;
    std::vector<int> results;

    // # statement
    if (arg0Type == SQLITE_INTEGER) {
        uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));

        // ## modifies at the statment number
        sql = "SELECT 1 FROM variables WHERE relation = 'modify' AND stmtNo = ? AND (name = ? OR ? = '') LIMIT 1;";
        results = db.selectFirstColumn<int>(sql, stmtNo, variableName, variableName);
        if (results.size() >= 1) {
            sqlite3_result_int(context, 1);
            return;
        }

        // ## for container statements
        sql = R"(
            WITH RECURSIVE parents_t AS (
                SELECT stmtNo, parentStmtNo FROM parents WHERE parentStmtNo = ?
                UNION ALL
                SELECT p.stmtNo, p.parentStmtNo FROM parents AS p
                INNER JOIN parents_t AS pt ON p.parentStmtNo = pt.stmtNo
            )
            SELECT 1
            FROM variables AS v
            WHERE relation = 'modify'
                AND EXISTS (SELECT 1 FROM parents_t AS pt WHERE pt.stmtNo = v.stmtNo)
                AND (name = ? OR ? = '')
            LIMIT 1;
        )";
        results = db.selectFirstColumn<int>(sql, stmtNo, variableName, variableName);
        if (results.size() >= 1) {
            sqlite3_result_int(context, 1);
            return;
        }

        // ## for call statements
        // TODO

        sqlite3_result_int(context, 0);
        return;
    }

    // # procedure
    // ## modifies directly
    std::string procedureName(reinterpret_cast<const char*>(sqlite3_value_text(argv[0])));
    sql = "SELECT 1 FROM variables WHERE relation = 'modify' AND procedureName = ? AND (name = ? OR ? = '') LIMIT 1;";
    results = db.selectFirstColumn<int>(sql, procedureName, variableName, variableName);
    if (results.size() >= 1) {
        sqlite3_result_int(context, 1);
        return;
    }

    // ## for call statements
    // TODO

    sqlite3_result_int(context, 0);
    return;
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
void Database::insertCall(uint32_t stmtNo, std::string callerName, std::string calleeName) {
    std::string insertStatementSQL = "INSERT INTO calls ('stmtNo', 'callerName', 'calleeName') VALUES(?, ?, ?)";
    db.execute(insertStatementSQL, stmtNo, callerName, calleeName);
}

// method to get data from the database
void Database::select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql) {
    db.select(dbResults, sql);
}
