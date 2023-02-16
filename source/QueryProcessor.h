#pragma once

#include <string>
#include <vector>
#include "Database.h"

class QueryProcessor {
public:
	// default constructor
	QueryProcessor();

	// destructor
	~QueryProcessor();

	// method for evaluating a query
	void evaluate(std::string query, std::vector<std::string>& results);
};
