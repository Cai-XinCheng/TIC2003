#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"

using namespace std;

class SQLiteWrapper {
public:
    // destructor
    ~SQLiteWrapper();

    // method to open to the database connection
    void open(const string& database);

    // method to close the database connection
    void close();

    // method to excute a query without return
    void execute(const string& sql);

    // method to excute a parameterized query without return
    template<typename... Args>
    void execute(const string& sql, Args&&... args);

    // method to excute a query and returns query result
    template<typename... Types>
    vector<tuple<Types...>> select(const string& sql);

    // method to excute a query and returns query result
    template<typename... Types>
    void select(vector<tuple<Types...>>& dbResults, const string& sql);

    // method to excute a parameterized query and returns query result
    template<typename... Types, typename... Args>
    vector<tuple<Types...>> select(const string& sql, Args&&... args);

    // method to excute a parameterized query and returns query result
    template<typename... Types, typename... Args>
    void select(vector<tuple<Types...>>& dbResults, const string& sql, Args&&... args);

    // method to excute a query and returns the first column of the query result
    template<typename T>
    vector<T> selectFirstColumn(const string& sql);

    // method to excute a query and returns the first column of the query result
    template<typename T>
    void selectFirstColumn(vector<T>& dbResults, const string& sql);

    // method to excute a parameterized query and returns the first column of the query result
    template<typename T, typename... Args>
    vector<T> selectFirstColumn(const string& sql, Args&&... args);

    // method to excute a parameterized query and returns the first column of the query result
    template<typename T, typename... Args>
    void selectFirstColumn(vector<T>& dbResults, const string& sql, Args&&... args);

private:
    // the connection pointer to the database
    sqlite3* db;

    // method to ensure SQLite result code is non-error
    static void ensureNonerror(sqlite3* db, int resultCode);

    // method to ensure SQLite result code is non-error
    static void ensureNonerror(sqlite3_stmt* statement, int resultCode);

    // method to prepare a SQLite statement
    static void prepare(sqlite3* db, const string& sql, sqlite3_stmt** statement);

    // method to bind int32 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int32_t aValue);

    // method to bind uint32 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const uint32_t aValue);

    // method to bind int64 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int64_t aValue);

    // method to bind dobule parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const double aValue);

    // method to bind string parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const string& value);

    // method to bind char* parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const char* value);

    // method to bind parameters
    template<typename T, typename... Args>
    static void bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first);

    // method to bind parameters
    template<typename T, typename... Args>
    static void bindParameters(sqlite3_stmt* preparedStatement, int index, T&& first, Args&&... args);

    // method to call SQLite step function and returns whether still contains data
    static bool step(sqlite3_stmt* preparedStatement);

    // method to get a column value as int32
    static void getColumn(sqlite3_stmt* preparedStatement, int index, int32_t& value);

    // method to get a column value as uint32
    static void getColumn(sqlite3_stmt* preparedStatement, int index, uint32_t& value);

    // method to get a column value as int64
    static void getColumn(sqlite3_stmt* preparedStatement, int index, int64_t& value);

    // method to get a column value as double
    static void getColumn(sqlite3_stmt* preparedStatement, int index, double& value);

    // method to get a column value as string
    static void getColumn(sqlite3_stmt* preparedStatement, int index, string& value);

    // method to get a row
    template<typename T>
    static tuple<T> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    // method to get a row
    template<typename T1, typename T2, typename... Types>
    static tuple<T1, T2, Types...> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    // method to get all rows with all columns
    template<typename... Types>
    static void getRowsWithAllColumns(sqlite3_stmt* preparedStatement, vector<tuple<Types...>>& dbResults);

    // method to get all rows with the first column only
    template<typename T>
    static void getRowsWithFirstColumn(sqlite3_stmt* preparedStatement, vector<T>& dbResults);

    // method to finalize SQLite statement
    static void finalize(sqlite3_stmt* preparedStatement);
};

#include "SQLiteWrapper.hpp"
