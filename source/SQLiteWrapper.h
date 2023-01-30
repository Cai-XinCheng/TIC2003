#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"

using namespace std;

class SQLiteWrapper {
public:
    void open(const string& database);
    void close();
    void execute(const string& query);
    vector<vector<string>> select(const string& query);
private:
    sqlite3* dbConnection;
    static vector<vector<string>> dbResults;
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};
