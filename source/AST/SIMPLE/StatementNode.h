#pragma once

#include "../ASTNode.h"
#include "ExpNode.h" 
#include <vector>
#include <string>

class StatementNode : public ASTNode {
public:
    explicit StatementNode(const uint32_t& stmtNo)
        : ASTNode(), stmtNo(stmtNo) {};
    void setStatementNode(StatementNode* stmtNode) { this->stmtNode = stmtNode; };
    std::string toString() const override;
    void setStmtType(const std::string& stmtType) { this->stmtType = stmtType; }
    uint32_t getStmtNo() { return stmtNo; }
    std::string getStmtType() { return stmtType; }
    StatementNode* getStmtNode() { return stmtNode; }
private:
    uint32_t stmtNo;
    std::string stmtType;
    StatementNode* stmtNode;
};

class ReadNode : public StatementNode {
public:
    explicit ReadNode(const uint32_t& stmtNo, const std::string& variableName) 
            : StatementNode(stmtNo), variableName(variableName) {};
    std::string toString() const override;
    std::string getVariableName() { return variableName; }
private:
    std::string variableName;
};

class PrintNode : public StatementNode {
public:
    explicit PrintNode(const uint32_t& stmtNo, const std::string& variableName) 
            : StatementNode(stmtNo), variableName(variableName) {};
    std::string toString() const override;
    std::string getVariableName() { return variableName; }
private:
    std::string variableName;
};

class AssignNode : public StatementNode {
public:
    explicit AssignNode(const uint32_t& stmtNo, const std::string& variableName, ExpNode* expression)
        : StatementNode(stmtNo), variableName(variableName), expression(expression) {};
    std::string toString() const override;
    std::string getVariableName() { return variableName; }
    ExpNode* getExpression() { return expression; }
private:
    std::string variableName;
    ExpNode* expression;
};

class WhileNode : public StatementNode {
public: 
    explicit WhileNode(const uint32_t& stmtNo, ExpNode* conExp)
            : StatementNode(stmtNo), conExp(conExp) {};
    std::string toString() const override;
    void setStatements(const std::vector<StatementNode*>& statements) { this->statements = statements; }
    ExpNode* getConExp() { return conExp; }
    std::vector<StatementNode*> getStatements() { return statements; }
private:
    ExpNode* conExp;
    std::vector<StatementNode*> statements;
};

class IfNode : public StatementNode {
public:
    explicit IfNode(const uint32_t& stmtNo, ExpNode* conExp)
            : StatementNode(stmtNo), conExp(conExp) {};
    std::string toString() const override;
    void setIfStatements(const std::vector<StatementNode*>& ifStatements) { this->ifStatements = ifStatements; }
    void setElseStatements(const std::vector<StatementNode*>& elseStatements) { this->elseStatements = elseStatements; }
    ExpNode* getConExp() { return conExp; }
    std::vector<StatementNode*> getIfStatements() { return ifStatements; }
    std::vector<StatementNode*> getElseStatements() { return elseStatements; }
private:
    ExpNode* conExp;
    std::vector<StatementNode*> ifStatements;
    std::vector<StatementNode*> elseStatements;
};

class CallNode : public StatementNode {
public:
    explicit CallNode(const uint32_t& stmtNo,const std::string& procedureName) 
            : StatementNode(stmtNo), procedureName(procedureName) {};
    std::string toString() const override;
    std::string getProcedureName() { return procedureName; }
private:
    std::string procedureName;
};
