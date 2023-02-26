#ifndef SQLITE_WRAPPER_HPP
#define SQLITE_WRAPPER_HPP

#include "SQLiteWrapper.h"
#include <stdexcept>

// destructor
inline SQLiteWrapper::~SQLiteWrapper() {
    sqlite3_close(db);
}

// method to open to the database connection
inline void SQLiteWrapper::open(const std::string& database) {
    const int ret = sqlite3_open(database.c_str(), &db);
    if (ret != SQLITE_OK) {
        throw std::invalid_argument("SQLiteWrapper: unable to open database");
    }
}

// method to close the database connection
inline void SQLiteWrapper::close() {
    int ret = sqlite3_close(db);
    if (ret != SQLITE_OK) {
        throw std::invalid_argument("SQLiteWrapper: unable to close database");
    }
}

// method to create a new user function
inline void SQLiteWrapper::createFunction(
    const char* zFunctionName,
    int nArg,
    int eTextRep,
    void* pApp,
    void (*xFunc)(sqlite3_context*, int, sqlite3_value**),
    void (*xStep)(sqlite3_context*, int, sqlite3_value**) = nullptr,
    void (*xFinal)(sqlite3_context*) = nullptr,
    void(*xDestroy)(void*) = nullptr
) {
    int ret = sqlite3_create_function_v2(db, zFunctionName, nArg, eTextRep, pApp, xFunc, xStep, xFinal, xDestroy);
    ensureNonerror(db, ret);
}

// method to excute a query without return
inline void SQLiteWrapper::execute(const std::string& sql) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        step(statement);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to excute a parameterized query without return
template<typename... Args>
inline void SQLiteWrapper::execute(const std::string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, std::forward<Args>(args)...);
        step(statement);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to excute a query and returns query result
template<typename... Types>
inline std::vector<std::tuple<Types...>> SQLiteWrapper::select(const std::string& sql) {
    std::vector<tuple<Types...>> dbResults;
    select<Types...>(dbResults, sql);

    return dbResults;
}

// method to excute a query and returns query result
inline std::vector<std::vector<std::string>> SQLiteWrapper::select(const std::string& sql) {
    std::vector<std::vector<std::string>> dbResults;
    select(dbResults, sql);

    return dbResults;
}

// method to excute a query and returns query result
template<typename... Types>
inline void SQLiteWrapper::select(std::vector<std::tuple<Types...>>& dbResults, const std::string& sql) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        getRowsWithAllColumns<Types...>(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to excute a query and returns query result
inline void SQLiteWrapper::select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        getRowsWithAllColumns(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}


// method to excute a parameterized query and returns query result
template<typename... Types, typename... Args>
inline std::vector<std::tuple<Types...>> SQLiteWrapper::select(const std::string& sql, Args&&... args) {
    std::vector<std::tuple<Types...>> dbResults;
    select<Types...>(dbResults, sql, std::forward<Args>(args)...);

    return dbResults;
}

// method to excute a parameterized query and returns query result
template<typename... Types, typename... Args>
inline void SQLiteWrapper::select(std::vector<std::tuple<Types...>>& dbResults, const std::string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, std::forward<Args>(args)...);
        getRowsWithAllColumns<Types...>(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to excute a query and returns the first column of the query result
template<typename T>
inline std::vector<T> SQLiteWrapper::selectFirstColumn(const std::string& sql) {
    std::vector<T> dbResults;
    selectFirstColumn<T>(dbResults, sql);

    return dbResults;
}

// method to excute a query and returns the first column of the query result
template<typename T>
inline void SQLiteWrapper::selectFirstColumn(std::vector<T>& dbResults, const std::string& sql) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        getRowsWithFirstColumn<T>(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to excute a parameterized query and returns the first column of the query result
template<typename T, typename... Args>
inline std::vector<T> SQLiteWrapper::selectFirstColumn(const std::string& sql, Args&&... args) {
    std::vector<T> dbResults;
    selectFirstColumn<T>(dbResults, sql, std::forward<Args>(args)...);

    return dbResults;
}

// method to excute a parameterized query and returns the first column of the query result
template<typename T, typename... Args>
inline void SQLiteWrapper::selectFirstColumn(std::vector<T>& dbResults, const std::string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, std::forward<Args>(args)...);
        getRowsWithFirstColumn<T>(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
}

// method to ensure SQLite result code is non-error
inline void SQLiteWrapper::ensureNonerror(sqlite3* db, int resultCode) {
    // https://www.sqlite.org/rescode.html#result_codes_versus_error_codes
    if (resultCode != SQLITE_OK && resultCode != SQLITE_ROW && resultCode != SQLITE_DONE) {
        const char* errorMessage = sqlite3_errmsg(db);
        throw std::runtime_error(("SQLiteWrapper: " + std::string(errorMessage)).c_str());
    }
}

// method to ensure SQLite result code is non-error
inline void SQLiteWrapper::ensureNonerror(sqlite3_stmt* statement, int resultCode) {
    sqlite3* db = sqlite3_db_handle(statement);
    ensureNonerror(db, resultCode);
}

// method to prepare a SQLite statement
inline void SQLiteWrapper::prepare(sqlite3* db, const std::string& sql, sqlite3_stmt** statement) {
    int ret = sqlite3_prepare_v2(db, sql.c_str(), static_cast<int>(sql.size()), statement, nullptr);
    ensureNonerror(db, ret);
}

// method to bind int32 parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const int32_t value) {
    const int ret = sqlite3_bind_int(preparedStatement, index, value);
    ensureNonerror(preparedStatement, ret);
}

// method to bind uint32 parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const uint32_t value) {
    const int ret = sqlite3_bind_int64(preparedStatement, index, value);
    ensureNonerror(preparedStatement, ret);
}

// method to bind int64 parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const int64_t value) {
    const int ret = sqlite3_bind_int64(preparedStatement, index, value);
    ensureNonerror(preparedStatement, ret);
}

// method to bind dobule parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const double value) {
    const int ret = sqlite3_bind_double(preparedStatement, index, value);
    ensureNonerror(preparedStatement, ret);
}

// method to bind string parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const std::string& value) {
    const int ret = sqlite3_bind_text(preparedStatement, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
    ensureNonerror(preparedStatement, ret);
}

// method to bind char* parameter
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const char* value) {
    const int ret = sqlite3_bind_text(preparedStatement, index, value, -1, SQLITE_TRANSIENT);
    ensureNonerror(preparedStatement, ret);
}

// method to bind parameters
template<typename T, typename... Args>
inline void SQLiteWrapper::bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first) {
    bindParameter(preparedStatement, index, std::forward<T>(first));
}

// method to bind parameters
template<typename T, typename... Args>
inline void SQLiteWrapper::bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args) {
    bindParameter(preparedStatement, index, std::forward<T>(first));
    bindParameters(preparedStatement, index + 1, std::forward<Args>(args)...);
}

// method to call SQLite step function and returns whether still contains data
inline bool SQLiteWrapper::step(sqlite3_stmt* preparedStatement) {
    const int ret = sqlite3_step(preparedStatement);
    ensureNonerror(preparedStatement, ret);

    return ret == SQLITE_ROW;
}

// method to get a column value as int32
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, int32_t& value) {
    value = sqlite3_column_int(preparedStatement, index);
}

// method to get a column value as uint32
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, uint32_t& value) {
    value = static_cast<unsigned>(sqlite3_column_int64(preparedStatement, index));
}

// method to get a column value as int64
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, int64_t& value) {
    value = sqlite3_column_int64(preparedStatement, index);
}

// method to get a column value as double
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, double& value) {
    value = sqlite3_column_double(preparedStatement, index);
}

// method to get a column value as string
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, std::string& value) {
    value = std::string(reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, index)));
}

// method to get a row
template<typename T>
inline std::tuple<T> SQLiteWrapper::getRow(sqlite3_stmt* preparedStatement, int columnIndex) {
    T value;
    getColumn(preparedStatement, columnIndex, value);

    return std::tie(value);
}

// method to get a row
template<typename T1, typename T2, typename... Types>
inline std::tuple<T1, T2, Types...> SQLiteWrapper::getRow(sqlite3_stmt* preparedStatement, int columnIndex) {
    T1 value;
    getColumn(preparedStatement, columnIndex, value);

    return tuple_cat(std::tie(value), getRow<T2, Types...>(preparedStatement, columnIndex + 1));
}

// method to get a row
inline void SQLiteWrapper::getRow(sqlite3_stmt* preparedStatement, std::vector<std::string>& dbRow) {
    int numberOfColumns = sqlite3_column_count(preparedStatement);
    for (int i = 0; i < numberOfColumns; i++) {
        std::string value;
        getColumn(preparedStatement, i, value);
        dbRow.push_back(value);
    }
}

// method to get all rows with all columns
template<typename... Types>
inline void SQLiteWrapper::getRowsWithAllColumns(sqlite3_stmt* preparedStatement, std::vector<std::tuple<Types...>>& dbResults) {
    for (;;) {
        if (!step(preparedStatement)) {
            break;
        }

        std::tuple<Types...> row = getRow<Types...>(preparedStatement);
        dbResults.push_back(row);
    }
}

// method to get all rows with all columns
inline void SQLiteWrapper::getRowsWithAllColumns(sqlite3_stmt* preparedStatement, std::vector<std::vector<std::string>>& dbResults) {
    for (;;) {
        if (!step(preparedStatement)) {
            break;
        }

        std::vector<std::string> dbRow;
        getRow(preparedStatement, dbRow);
        dbResults.push_back(dbRow);
    }
}

// method to get all rows with the first column only
template<typename T>
inline void SQLiteWrapper::getRowsWithFirstColumn(sqlite3_stmt* preparedStatement, std::vector<T>& dbResults) {
    for (;;) {
        if (!step(preparedStatement)) {
            break;
        }

        T value;
        getColumn(preparedStatement, 0, value);
        dbResults.push_back(value);
    }
}

// method to finalize SQLite statement
inline void SQLiteWrapper::finalize(sqlite3_stmt* preparedStatement) {
    const int ret = sqlite3_finalize(preparedStatement);
    ensureNonerror(preparedStatement, ret);
}

#endif // !SQLITE_WRAPPER_HPP
