#ifndef SQLITE_WRAPPER_HPP
#define SQLITE_WRAPPER_HPP

#include "SQLiteWrapper.h"

// destructor
inline SQLiteWrapper::~SQLiteWrapper() {
    sqlite3_close(db);
}

// method to open to the database connection
inline void SQLiteWrapper::open(const string& database) {
    const int ret = sqlite3_open(database.c_str(), &db);
    if (ret != SQLITE_OK) {
        throw std::exception("SQLiteWrapper: unable to open database");
    }
}

// method to close the database connection
inline void SQLiteWrapper::close() {
    int ret = sqlite3_close(db);
    if (ret != SQLITE_OK) {
        throw std::exception("SQLiteWrapper: unable to close database");
    }
}

// method to excute a query without return
inline void SQLiteWrapper::execute(const string& sql) {
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
inline void SQLiteWrapper::execute(const string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, forward<Args>(args)...);
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
inline vector<tuple<Types...>> SQLiteWrapper::select(const string& sql) {
    vector<tuple<Types...>> dbResults;
    select<Types...>(dbResults, sql);

    return dbResults;
}

// method to excute a query and returns query result
template<typename... Types>
inline void SQLiteWrapper::select(vector<tuple<Types...>>& dbResults, const string& sql) {
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

// method to excute a parameterized query and returns query result
template<typename... Types, typename... Args>
inline vector<tuple<Types...>> SQLiteWrapper::select(const string& sql, Args&&... args) {
    vector<tuple<Types...>> dbResults;
    select<Types...>(dbResults, sql, forward<Args>(args)...);

    return dbResults;
}

// method to excute a parameterized query and returns query result
template<typename... Types, typename... Args>
inline void SQLiteWrapper::select(vector<tuple<Types...>>& dbResults, const string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, forward<Args>(args)...);
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
inline vector<T> SQLiteWrapper::selectFirstColumn(const string& sql) {
    vector<T> dbResults;
    selectFirstColumn<T>(dbResults, sql);

    return dbResults;
}

// method to excute a query and returns the first column of the query result
template<typename T>
inline void SQLiteWrapper::selectFirstColumn(vector<T>& dbResults, const string& sql) {
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
inline vector<T> SQLiteWrapper::selectFirstColumn(const string& sql, Args&&... args) {
    vector<T> dbResults;
    selectFirstColumn<T>(dbResults, sql, forward<Args>(args)...);

    return dbResults;
}

// method to excute a parameterized query and returns the first column of the query result
template<typename T, typename... Args>
inline void SQLiteWrapper::selectFirstColumn(vector<T>& dbResults, const string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bindParameters(statement, 1, forward<Args>(args)...);
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
        throw std::exception(("SQLiteWrapper: " + string(errorMessage)).c_str());
    }
}

// method to ensure SQLite result code is non-error
inline void SQLiteWrapper::ensureNonerror(sqlite3_stmt* statement, int resultCode) {
    sqlite3* db = sqlite3_db_handle(statement);
    ensureNonerror(db, resultCode);
}

// method to prepare a SQLite statement
inline void SQLiteWrapper::prepare(sqlite3* db, const string& sql, sqlite3_stmt** statement) {
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
inline void SQLiteWrapper::bindParameter(sqlite3_stmt* preparedStatement, int index, const string& value) {
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
    bindParameter(preparedStatement, index, first);
}

// method to bind parameters
template<typename T, typename... Args>
inline void SQLiteWrapper::bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args) {
    bindParameter(preparedStatement, index, first);
    bindParameters(preparedStatement, index + 1, forward<Args>(args)...);
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
inline void SQLiteWrapper::getColumn(sqlite3_stmt* preparedStatement, int index, string& value) {
    value = string(reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, index)));
}

// method to get a row
template<typename T>
inline tuple<T> SQLiteWrapper::getRow(sqlite3_stmt* preparedStatement, int columnIndex) {
    T value;
    getColumn(preparedStatement, columnIndex, value);

    return tie(value);
}

// method to get a row
template<typename T1, typename T2, typename... Types>
inline tuple<T1, T2, Types...> SQLiteWrapper::getRow(sqlite3_stmt* preparedStatement, int columnIndex) {
    T1 value;
    getColumn(preparedStatement, columnIndex, value);

    return tuple_cat(tie(value), getRow<T2, Types...>(preparedStatement, columnIndex + 1));
}

// method to get all rows with all columns
template<typename... Types>
inline void SQLiteWrapper::getRowsWithAllColumns(sqlite3_stmt* preparedStatement, vector<tuple<Types...>>& dbResults) {
    int columnsCount = -1;
    for (;;) {
        if (!step(preparedStatement)) {
            break;
        }

        tuple<Types...> row = getRow<Types...>(preparedStatement);
        dbResults.push_back(row);
    }
}

// method to get all rows with the first column only
template<typename T>
inline void SQLiteWrapper::getRowsWithFirstColumn(sqlite3_stmt* preparedStatement, vector<T>& dbResults) {
    int columnsCount = -1;
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
