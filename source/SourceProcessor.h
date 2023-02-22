#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include "Database.h"
#include "Tokenizer.h"

class SourceProcessor {
public:
	// method for processing the source program
	void process(string program);
    void processToken(vector<string> token);
    void processSingleStmt(vector<string> statement);
};
