#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include "Database.h"
#include "Tokenizer.h"
#include "AST/Expression/ExpressionNode.h"
#include "AST/SIMPLE/StatementNode.h"
#include "AST/SIMPLE/ProcedureNode.h"
#include "set"
#include "stack"
#include "vector"

class SourceProcessor {
public:
	// method for processing the source program
	void process(std::string input);

private:
    std::set<int64_t> cons;
    std::stack<const StatementNode*> parent;
    void processProcedure(const ProcedureNode* procedureNode);
    void processStatement(const int& i, const std::string& procedureName, const std::vector<const StatementNode*>& statements, const uint32_t& nextStmtNo);
    void processExp(const ExpressionNode* expression, const uint32_t& stmtNo, const std::string& procedureName);
};
