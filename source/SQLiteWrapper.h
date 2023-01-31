#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"

using namespace std;

class SQLiteWrapper {
public:
    ~SQLiteWrapper();

    void open(const string& database);

    void close();

    void execute(const string& sql);

    template<typename... Args>
    void execute(const string& sql, Args&&... args);

    vector<vector<string>> select(const string& sql);

    template<typename... Args>
    vector<vector<string>> select(const string& sql, Args&&... args);

private:
    sqlite3* db;

    static void ensure_sqlite3_success(sqlite3* db, int resultCode);

    static void ensure_sqlite3_success(sqlite3_stmt* statement, int resultCode);

    static void prepare(sqlite3* db, const string& sql, sqlite3_stmt** statement);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const int32_t aValue);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const uint32_t aValue);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const int64_t aValue);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const double aValue);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const string& value);

    static void bind_parameter(sqlite3_stmt* preparedStatement, int index, const char* value);

    template<typename T, typename... Args>
    static void bind_parameters(sqlite3_stmt* preparedStatement, int index, T&& first);

    template<typename T, typename... Args>
    static void bind_parameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args);

    static bool step(sqlite3_stmt* preparedStatement);

    static void steps(sqlite3_stmt* preparedStatement, vector<vector<string>>& dbResults);

    static void finalize(sqlite3_stmt* preparedStatement);
};

#include "SQLiteWrapper.hpp"
