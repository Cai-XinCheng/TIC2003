#pragma once

#include "FilterClause.h"
#include <string>

class SuchThatClause : public FilterClause {
public:
    explicit SuchThatClause(const std::string& relationshipName, const std::string& relationshipArg1, const std::string& relationshipArg2);
    void getRelationshipName(std::string& relationshipNameRef) const;
    void getRelationshipArg1(std::string& relationshipArg1Ref) const;
    void getRelationshipArg2(std::string& relationshipArg2Ref) const;

private:
    std::string relationshipName;
    std::string relationshipArg1;
    std::string relationshipArg2;
};
