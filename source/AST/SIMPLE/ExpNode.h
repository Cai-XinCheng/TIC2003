#pragma once

#include "../ASTNode.h"

// expr: expr '+' term | expr '-' term | term
class ExpNode : public ASTNode {
public:
    explicit ExpNode(const std::string& operate, ExpNode* lhs, ExpNode* rhs)
            : ASTNode(), lhs(lhs), rhs(rhs), operate(operate) {};
    explicit ExpNode() {};
    std::string toString() const override;
    ExpNode* getLhs() { return lhs; }
    ExpNode* getRhs() { return rhs; }
private:
    ExpNode* lhs;
    ExpNode* rhs;
    std::string operate;
};

// term: term '*' factor | term '/' factor | term '%' factor | factor
class TermNode : public ExpNode {
public:
    explicit TermNode(const std::string& operate, ExpNode* lhs, ExpNode* rhs)
        : ExpNode(operate, lhs, rhs){};
};

class VarNode : public ExpNode {
public:
    explicit VarNode(const std::string& varName) : ExpNode(), variableName(varName) {};
    std::string toString() const override;
    std::string getVariableName() { return variableName; }
private:
    std::string variableName;
};

class ConstNode : public ExpNode {
public:
    explicit ConstNode(const uint32_t& value) : ExpNode(), value(value) {};
    std::string toString() const override;
    uint32_t getValue() { return value; }
private:
    uint32_t value;
};

// cond_expr: rel_factor '>' rel_factor | rel_factor '<' rel_factor
// rel_factor: var_name | const_value | expr
class ConExpNode : public ExpNode {
public:
    explicit ConExpNode(const std::string& operate, ExpNode* lhs, ExpNode* rhs)
            : ExpNode(operate, lhs, rhs) {};
};
