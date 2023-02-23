#pragma once

#include "FilterClause.h"
#include <string>
#include <format>

class SuchThatClause : public FilterClause {
public:
    explicit SuchThatClause(const std::string& relationshipName, const std::string& relationshipArg1, const std::string& relationshipArg2);
    std::string toString() const override;
    std::string getRelationshipName() const;
    std::string getRelationshipArg1() const;
    std::string getRelationshipArg2() const;

private:
    std::string relationshipName;
    std::string relationshipArg1;
    std::string relationshipArg2;
};
