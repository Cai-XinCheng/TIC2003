#pragma once

#include "../ASTNode.h"
#include "../SIMPLE/Program.h"
#include <vector>
#include <string>

class ProgramParser {
public:
    ProgramParser(const std::vector<std::string>& tokens) : tokens(tokens) {};
    Program parse();
    ProcedureNode parseProcedure();
    StatementNode* parseStatement();
    ReadNode* parseRead();
    PrintNode* parsePrint();
    AssignNode* parseAssign();
    WhileNode* parseWhile();
    IfNode* parseIf();
    CallNode* parseCall();
private:
    uint32_t stmtNo = 1;
    unsigned int i = 0;
    std::vector<std::string> tokens;
};
