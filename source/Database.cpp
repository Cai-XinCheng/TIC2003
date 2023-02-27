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
    db.createFunction("check_call", 2, SQLITE_ANY, nullptr, &sqlite3_check_call);
    db.createFunction("check_call_t", 2, SQLITE_ANY, nullptr, &sqlite3_check_call_t);
    db.createFunction("check_modify", -1, SQLITE_ANY, nullptr, &sqlite3_check_modify);
    db.createFunction("check_use", -1, SQLITE_ANY, nullptr, &sqlite3_check_use);
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

    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

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

    uint32_t parentStmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[0]));
    uint32_t stmtNo = static_cast<unsigned>(sqlite3_value_int64(argv[1]));

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

// sqlite3 user function to check whether a specified object calls a specified variable or any variable
void Database::sqlite3_check_call(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_call", -1);
        return;
    }

    int arg0Type = sqlite3_value_type(argv[0]);
    int arg1Type = sqlite3_value_type(argv[1]);
    if ((arg0Type != SQLITE_TEXT && arg0Type != SQLITE_NULL) || (arg1Type != SQLITE_TEXT && arg1Type != SQLITE_NULL)) {
        sqlite3_result_error(context, "invalid argument type of check_call", -1);
        return;
    }

    if (arg0Type == SQLITE_NULL && arg1Type == SQLITE_NULL) {
        sqlite3_result_int(context, 1);
        return;
    }

    std::string callerName = arg0Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[0]))) : "";
    std::string calleeName = arg1Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[1]))) : "";
    if (arg0Type == SQLITE_NULL) {
        std::string sql = "SELECT 1 FROM calls WHERE calleeName = ?;";
        std::vector<int> results = db.selectFirstColumn<int>(sql, calleeName);
        int result = results.size() >= 1 ? 1 : 0;
        sqlite3_result_int(context, result);
        return;
    }
    
    if (arg1Type == SQLITE_NULL) {
        std::string sql = "SELECT 1 FROM calls WHERE callerName = ?;";
        std::vector<int> results = db.selectFirstColumn<int>(sql, callerName);
        int result = results.size() >= 1 ? 1 : 0;
        sqlite3_result_int(context, result);
        return;
    }

    std::string sql = "SELECT 1 FROM calls WHERE callerName = ? AND calleeName = ?;";
    std::vector<int> results = db.selectFirstColumn<int>(sql, callerName, calleeName);
    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
    return;
}

// sqlite3 user function to check whether a specified object calls (directly or indirectly) a specified variable or any variable
void Database::sqlite3_check_call_t(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_call", -1);
        return;
    }

    int arg0Type = sqlite3_value_type(argv[0]);
    int arg1Type = sqlite3_value_type(argv[1]);
    if ((arg0Type != SQLITE_TEXT && arg0Type != SQLITE_NULL) || (arg1Type != SQLITE_TEXT && arg1Type != SQLITE_NULL)) {
        sqlite3_result_error(context, "invalid argument type of check_call", -1);
        return;
    }

    if (arg0Type == SQLITE_NULL && arg1Type == SQLITE_NULL) {
        sqlite3_result_int(context, 1);
        return;
    }

    std::string callerName = arg0Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[0]))) : "";
    std::string calleeName = arg1Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[1]))) : "";
    if (arg0Type == SQLITE_NULL) {
        std::string sql = "SELECT 1 FROM calls WHERE calleeName = ?;";
        std::vector<int> results = db.selectFirstColumn<int>(sql, calleeName);
        int result = results.size() >= 1 ? 1 : 0;
        sqlite3_result_int(context, result);
        return;
    }

    if (arg1Type == SQLITE_NULL) {
        std::string sql = "SELECT 1 FROM calls WHERE callerName = ?;";
        std::vector<int> results = db.selectFirstColumn<int>(sql, callerName);
        int result = results.size() >= 1 ? 1 : 0;
        sqlite3_result_int(context, result);
        return;
    }

    std::string sql = R"(
        WITH RECURSIVE calls_t AS (
            SELECT callerName, calleeName FROM calls WHERE callerName = ?
            UNION ALL
            SELECT c.callerName, c.calleeName FROM calls AS c
            INNER JOIN calls_t AS ct ON ct.calleeName = c.callerName
            WHERE ct.calleeName != ?
        )
        SELECT 1 FROM calls_t WHERE calleeName = ? LIMIT 1;
    )";
    std::vector<int> results = db.selectFirstColumn<int>(sql, callerName, calleeName, calleeName);
    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
    return;
}

// sqlite3 user function to check whether a specified object modifies a specified variable or any variable
void Database::sqlite3_check_modify(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_modify", -1);
        return;
    }

    int arg0Type = sqlite3_value_type(argv[0]);
    int arg1Type = sqlite3_value_type(argv[1]);
    if ((arg0Type != SQLITE_INTEGER && arg0Type != SQLITE_TEXT) || (arg1Type != SQLITE_TEXT && arg1Type != SQLITE_NULL)) {
        sqlite3_result_error(context, "invalid argument type of check_modify", -1);
        return;
    }

    uint32_t stmtNo = arg0Type == SQLITE_INTEGER ? static_cast<unsigned>(sqlite3_value_int64(argv[0])) : 0;
    std::string procedureName = arg0Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[0]))) : "";
    std::string variableName = arg1Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[1]))) : "";

    std::string sql = std::format(R"(
        WITH RECURSIVE parents_t AS (
            SELECT stmtNo, parentStmtNo FROM parents WHERE parentStmtNo = ?
            UNION ALL
            SELECT p.stmtNo, p.parentStmtNo FROM parents AS p
            INNER JOIN parents_t AS pt ON p.parentStmtNo = pt.stmtNo
        ),
        stmt_nos AS (
            SELECT stmtNo FROM parents_t
            UNION ALL
            SELECT ?
        ),
        initial_calls AS (
            SELECT callerName, calleeName FROM calls AS c1 WHERE EXISTS (SELECT 1 FROM stmt_nos AS sn WHERE sn.stmtNo = c1.stmtNo)
            UNION ALL
            SELECT '', ? WHERE ? = {}
        ),
        called_procedures_t AS (
            SELECT callerName, calleeName FROM initial_calls
            UNION ALL
            SELECT c2.callerName, c2.calleeName FROM calls AS c2
            INNER JOIN called_procedures_t AS cpt ON cpt.calleeName = c2.callerName
        )
        SELECT 1
        FROM variables AS v
        WHERE relation = 'modify'
            AND (EXISTS (SELECT 1 FROM stmt_nos AS sn WHERE sn.stmtNo = v.stmtNo)
                OR EXISTS (SELECT 1 FROM called_procedures_t AS cpt WHERE cpt.calleeName = v.procedureName))
            AND ({} OR name = ?)
        LIMIT 1;
    )", std::to_string(SQLITE_TEXT), arg1Type == SQLITE_NULL ? "TRUE" : "FALSE");
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, stmtNo, procedureName, arg0Type, variableName);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
}

// sqlite3 user function to check whether a specified object uses a specified variable or any variable
void Database::sqlite3_check_use(sqlite3_context* context, int argc, sqlite3_value** argv) {
    if (argc != 2) {
        sqlite3_result_error(context, "invalid number of arguments of check_use", -1);
        return;
    }

    int arg0Type = sqlite3_value_type(argv[0]);
    int arg1Type = sqlite3_value_type(argv[1]);
    if ((arg0Type != SQLITE_INTEGER && arg0Type != SQLITE_TEXT) || (arg1Type != SQLITE_TEXT && arg1Type != SQLITE_NULL)) {
        sqlite3_result_error(context, "invalid argument type of check_use", -1);
        return;
    }

    uint32_t stmtNo = arg0Type == SQLITE_INTEGER ? static_cast<unsigned>(sqlite3_value_int64(argv[0])) : 0;
    std::string procedureName = arg0Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[0]))) : "";
    std::string variableName = arg1Type == SQLITE_TEXT ? std::string(reinterpret_cast<const char*>(sqlite3_value_text(argv[1]))) : "";

    std::string sql = std::format(R"(
        WITH RECURSIVE parents_t AS (
            SELECT stmtNo, parentStmtNo FROM parents WHERE parentStmtNo = ?
            UNION ALL
            SELECT p.stmtNo, p.parentStmtNo FROM parents AS p
            INNER JOIN parents_t AS pt ON p.parentStmtNo = pt.stmtNo
        ),
        stmt_nos AS (
            SELECT stmtNo FROM parents_t
            UNION ALL
            SELECT ?
        ),
        initial_calls AS (
            SELECT callerName, calleeName FROM calls AS c1 WHERE EXISTS (SELECT 1 FROM stmt_nos AS sn WHERE sn.stmtNo = c1.stmtNo)
            UNION ALL
            SELECT '', ? WHERE ? = {}
        ),
        called_procedures_t AS (
            SELECT callerName, calleeName FROM initial_calls
            UNION ALL
            SELECT c2.callerName, c2.calleeName FROM calls AS c2
            INNER JOIN called_procedures_t AS cpt ON cpt.calleeName = c2.callerName
        )
        SELECT 1
        FROM variables AS v
        WHERE relation = 'use'
            AND (EXISTS (SELECT 1 FROM stmt_nos AS sn WHERE sn.stmtNo = v.stmtNo)
                OR EXISTS (SELECT 1 FROM called_procedures_t AS cpt WHERE cpt.calleeName = v.procedureName))
            AND ({} OR name = ?)
        LIMIT 1;
    )", std::to_string(SQLITE_TEXT), arg1Type == SQLITE_NULL ? "TRUE" : "FALSE");
    std::vector<int> results = db.selectFirstColumn<int>(sql, stmtNo, stmtNo, procedureName, arg0Type, variableName);

    int result = results.size() >= 1 ? 1 : 0;
    sqlite3_result_int(context, result);
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
