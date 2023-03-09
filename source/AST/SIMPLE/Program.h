#pragma once

#include "ProcedureNode.h"

class Program : public ASTNode {
public:
    static const std::string& type;
    explicit Program(const std::vector<const ProcedureNode*>& procedures);
    ~Program() override;
    std::string toString() const override;
    std::vector<const ProcedureNode*> getProcedures() const;

private:
    std::vector<const ProcedureNode*> procedures;
};
