#ifndef SQLITE_WRAPPER_HPP
#define SQLITE_WRAPPER_HPP

#include "SQLiteWrapper.h"

inline SQLiteWrapper::~SQLiteWrapper() {
    sqlite3_close(db);
}

inline void SQLiteWrapper::open(const string& database) {
    const int ret = sqlite3_open(database.c_str(), &db);
    if (ret != SQLITE_OK) {
        throw std::exception("SQLiteWrapper: unable to open database");
    }
}

inline void SQLiteWrapper::close() {
    int ret = sqlite3_close(db);
    if (ret != SQLITE_OK) {
        throw std::exception("SQLiteWrapper: unable to close database");
    }
}

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

template<typename... Args>
inline void SQLiteWrapper::execute(const string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;

    try {
        prepare(db, sql, &statement);
        bind_parameters(statement, 1, forward<Args>(args)...);
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

inline vector<vector<string>> SQLiteWrapper::select(const string& sql) {
    sqlite3_stmt* statement = nullptr;
    vector<vector<string>> dbResults;

    try {
        prepare(db, sql, &statement);
        steps(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
    return dbResults;
}

template<typename... Args>
inline vector<vector<string>> SQLiteWrapper::select(const string& sql, Args&&... args) {
    sqlite3_stmt* statement = nullptr;
    vector<vector<string>> dbResults;

    try {
        prepare(db, sql, &statement);
        bind_parameters(statement, 1, forward<Args>(args)...);
        steps(statement, dbResults);
    }
    catch (...) {
        if (statement != nullptr) {
            finalize(statement);
        }
        throw;
    }
    finalize(statement);
    return dbResults;
}

inline void SQLiteWrapper::ensure_sqlite3_success(sqlite3* db, int resultCode) {
    // https://www.sqlite.org/rescode.html#result_codes_versus_error_codes
    if (resultCode != SQLITE_OK && resultCode != SQLITE_ROW && resultCode != SQLITE_DONE) {
        const char* errorMessage = sqlite3_errmsg(db);
        throw std::exception(("SQLiteWrapper: " + string(errorMessage)).c_str());
    }
}

inline void SQLiteWrapper::ensure_sqlite3_success(sqlite3_stmt* statement, int resultCode) {
    sqlite3* db = sqlite3_db_handle(statement);
    ensure_sqlite3_success(db, resultCode);
}

inline void SQLiteWrapper::prepare(sqlite3* db, const string& sql, sqlite3_stmt** statement) {
    int ret = sqlite3_prepare_v2(db, sql.c_str(), static_cast<int>(sql.size()), statement, nullptr);
    ensure_sqlite3_success(db, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const int32_t value) {
    const int ret = sqlite3_bind_int(preparedStatement, index, value);
    ensure_sqlite3_success(preparedStatement, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const uint32_t value) {
    const int ret = sqlite3_bind_int64(preparedStatement, index, value);
    ensure_sqlite3_success(preparedStatement, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const int64_t value) {
    const int ret = sqlite3_bind_int64(preparedStatement, index, value);
    ensure_sqlite3_success(preparedStatement, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const double value) {
    const int ret = sqlite3_bind_double(preparedStatement, index, value);
    ensure_sqlite3_success(preparedStatement, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const string& value) {
    const int ret = sqlite3_bind_text(preparedStatement, index, value.c_str(), static_cast<int>(value.size()), SQLITE_TRANSIENT);
    ensure_sqlite3_success(preparedStatement, ret);
}

inline void SQLiteWrapper::bind_parameter(sqlite3_stmt* preparedStatement, int index, const char* value) {
    const int ret = sqlite3_bind_text(preparedStatement, index, value, -1, SQLITE_TRANSIENT);
    ensure_sqlite3_success(preparedStatement, ret);
}

template<typename T, typename... Args>
inline void SQLiteWrapper::bind_parameters(sqlite3_stmt* preparedStatement, int index, T&& first) {
    bind_parameter(preparedStatement, index, first);
}

template<typename T, typename... Args>
inline void SQLiteWrapper::bind_parameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args) {
    bind_parameter(preparedStatement, index, first);
    bind_parameters(preparedStatement, index + 1, forward<Args>(args)...);
}

inline bool SQLiteWrapper::step(sqlite3_stmt* preparedStatement) {
    const int ret = sqlite3_step(preparedStatement);
    ensure_sqlite3_success(preparedStatement, ret);
    return ret == SQLITE_ROW;
}

inline void SQLiteWrapper::steps(sqlite3_stmt* preparedStatement, vector<vector<string>>& dbResults) {
    int columnsCount = -1;
    for (;;) {
        if (!step(preparedStatement)) {
            break;
        }
        if (columnsCount == -1) {
            columnsCount = sqlite3_data_count(preparedStatement);
        }
        vector<string> dbRow;
        for (int i = 0; i < columnsCount; i++) {
            const string columnValue = string(reinterpret_cast<const char*>(sqlite3_column_text(preparedStatement, i)));
            dbRow.push_back(columnValue);
        }
        dbResults.push_back(dbRow);
    }
}

inline void SQLiteWrapper::finalize(sqlite3_stmt* preparedStatement) {
    const int ret = sqlite3_finalize(preparedStatement);
    ensure_sqlite3_success(preparedStatement, ret);
}

#endif // !SQLITE_WRAPPER_HPP
