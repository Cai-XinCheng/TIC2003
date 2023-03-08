#pragma once

#include "AST/SIMPLE/Program.h"
#include "AST/SIMPLE/ReadNode.h"
#include "AST/SIMPLE/PrintNode.h"
#include "AST/SIMPLE/AssignNode.h"
#include "AST/SIMPLE/WhileNode.h"
#include "AST/SIMPLE/IfNode.h"
#include "AST/SIMPLE/CallNode.h"
#include "AST/SIMPLE/ConExpNode.h"
#include "ExpressionParser.h";
#include <vector>
#include <string>

class ProgramParser {
public:
    explicit ProgramParser(const std::vector<std::string>& tokens);
    Program parse();

private:
    uint32_t stmtNo = 1;
    unsigned int i = 0;
    std::vector<std::string> tokens;
    ExpressionParser ep;
    const ProcedureNode* parseProcedure();
    const StatementNode* parseStatement();
    const ReadNode* parseRead();
    const PrintNode* parsePrint();
    const AssignNode* parseAssign();
    const WhileNode* parseWhile();
    const IfNode* parseIf();
    const CallNode* parseCall();
};
