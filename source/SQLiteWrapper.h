#pragma once

#include "sqlite3.h"
#include <string>
#include <tuple>
#include <vector>

class SQLiteWrapper {
public:
    // destructor
    ~SQLiteWrapper();

    // method to open to the database connection
    void open(const std::string& database);

    // method to close the database connection
    void close();

    // method to create a new user function
    void createFunction(
        const char* zFunctionName,
        int nArg,
        int eTextRep,
        void* pApp,
        void (*xFunc)(sqlite3_context*, int, sqlite3_value**),
        void (*xStep)(sqlite3_context*, int, sqlite3_value**),
        void (*xFinal)(sqlite3_context*),
        void(*xDestroy)(void*)
    );

    // method to excute a query without return
    void execute(const std::string& sql);

    // method to excute a parameterized query without return
    template<typename... Args>
    void execute(const std::string& sql, Args&&... args);

    // method to excute a query and returns query result
    template<typename... Types>
    std::vector<std::tuple<Types...>> select(const std::string& sql);

    // method to excute a query and returns query result
    std::vector<std::vector<std::string>> select(const std::string& sql);

    // method to excute a query and returns query result
    template<typename... Types>
    void select(std::vector<std::tuple<Types...>>& dbResults, const std::string& sql);

    // method to excute a query and returns query result
    void select(std::vector<std::vector<std::string>>& dbResults, const std::string& sql);

    // method to excute a parameterized query and returns query result
    template<typename... Types, typename... Args>
    std::vector<std::tuple<Types...>> select(const std::string& sql, Args&&... args);

    // method to excute a parameterized query and returns query result
    template<typename... Types, typename... Args>
    void select(std::vector<std::tuple<Types...>>& dbResults, const std::string& sql, Args&&... args);

    // method to excute a query and returns the first column of the query result
    template<typename T>
    std::vector<T> selectFirstColumn(const std::string& sql);

    // method to excute a query and returns the first column of the query result
    template<typename T>
    void selectFirstColumn(std::vector<T>& dbResults, const std::string& sql);

    // method to excute a parameterized query and returns the first column of the query result
    template<typename T, typename... Args>
    std::vector<T> selectFirstColumn(const std::string& sql, Args&&... args);

    // method to excute a parameterized query and returns the first column of the query result
    template<typename T, typename... Args>
    void selectFirstColumn(std::vector<T>& dbResults, const std::string& sql, Args&&... args);

private:
    // the connection pointer to the database
    sqlite3* db;

    // method to ensure SQLite result code is non-error
    static void ensureNonerror(sqlite3* db, int resultCode);

    // method to ensure SQLite result code is non-error
    static void ensureNonerror(sqlite3_stmt* statement, int resultCode);

    // method to prepare a SQLite statement
    static void prepare(sqlite3* db, const std::string& sql, sqlite3_stmt** statement);

    // method to bind int32 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int32_t aValue);

    // method to bind uint32 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const uint32_t aValue);

    // method to bind int64 parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const int64_t aValue);

    // method to bind dobule parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const double aValue);

    // method to bind string parameter
    static void bindParameter(sqlite3_stmt* preparedStatement, int index, const std::string& value);

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
    static void getColumn(sqlite3_stmt* preparedStatement, int index, std::string& value);

    // method to get a row
    template<typename T>
    static std::tuple<T> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    // method to get a row
    template<typename T1, typename T2, typename... Types>
    static std::tuple<T1, T2, Types...> getRow(sqlite3_stmt* preparedStatement, int columnIndex = 0);

    // method to get a row
    static void getRow(sqlite3_stmt* preparedStatement, std::vector<std::string>& dbRow);

    // method to get all rows with all columns
    template<typename... Types>
    static void getRowsWithAllColumns(sqlite3_stmt* preparedStatement, std::vector<std::tuple<Types...>>& dbResults);

    // method to get all rows with all columns
    static void getRowsWithAllColumns(sqlite3_stmt* preparedStatement, std::vector<std::vector<std::string>>& dbResults);

    // method to get all rows with the first column only
    template<typename T>
    static void getRowsWithFirstColumn(sqlite3_stmt* preparedStatement, std::vector<T>& dbResults);

    // method to finalize SQLite statement
    static void finalize(sqlite3_stmt* preparedStatement);
};

#include "SQLiteWrapper.hpp"
