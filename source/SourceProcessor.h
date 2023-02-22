#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include "Database.h"
#include "Tokenizer.h"

class SourceProcessor {
public:
	// method for processing the source program
	void process(std::string program);
    void processToken(std::vector<std::string> token);
    void processSingleStmt(std::vector<std::string> statement);
};
