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

    template<typename... Types>
    vector<tuple<Types...>> select(const string& sql);

    template<typename... Types>
    void select(vector<tuple<Types...>>& dbResults, const string& sql);

    template<typename... Types, typename... Args>
    vector<tuple<Types...>> select(const string& sql, Args&&... args);

    template<typename... Types, typename... Args>
    void select(vector<tuple<Types...>>& dbResults, const string& sql, Args&&... args);

    template<typename T>
    vector<T> selectFirstColumn(const string& sql);

    template<typename T>
    void selectFirstColumn(vector<T>& dbResults, const string& sql);

    template<typename T, typename... Args>
    vector<T> selectFirstColumn(const string& sql, Args&&... args);

    template<typename T, typename... Args>
    void selectFirstColumn(vector<T>& dbResults, const string& sql, Args&&... args);

private:
    sqlite3* db;

    static void ensureNonerror(sqlite3* db, int resultCode);

    static void ensureNonerror(sqlite3_stmt* statement, int resultCode);

    static void prepare(sqlite3* db, const string& sql, sqlite3_stmt** statement);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int32_t aValue);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const uint32_t aValue);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int64_t aValue);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const double aValue);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const string& value);

    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const char* value);

    template<typename T, typename... Args>
    static void bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first);

    template<typename T, typename... Args>
    static void bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args);

    static bool step(sqlite3_stmt* preparedStatement);

    static void getColumn(sqlite3_stmt* preparedStatement, int index, int32_t& value);

    static void getColumn(sqlite3_stmt* preparedStatement, int index, uint32_t& value);

    static void getColumn(sqlite3_stmt* preparedStatement, int index, int64_t& value);

    static void getColumn(sqlite3_stmt* preparedStatement, int index, double& value);

    static void getColumn(sqlite3_stmt* preparedStatement, int index, string& value);

    template<typename T>
    static tuple<T> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    template<typename T1, typename T2, typename... Types>
    static tuple<T1, T2, Types...> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    template<typename... Types>
    static void getRowsWithAllColumns(sqlite3_stmt* preparedStatement, vector<tuple<Types...>>& dbResults);

    template<typename T>
    static void getRowsWithFirstColumn(sqlite3_stmt* preparedStatement, vector<T>& dbResults);

    static void finalize(sqlite3_stmt* preparedStatement);
};

#include "SQLiteWrapper.hpp"
