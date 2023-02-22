#pragma once

#include "SuchThatClause.h"
#include <string>

SuchThatClause::SuchThatClause(const std::string& relationshipName, const std::string& relationshipArg1, const std::string& relationshipArg2)
    : FilterClause("SuchThatClause"), relationshipName(relationshipName), relationshipArg1(relationshipArg1), relationshipArg2(relationshipArg2) {
}

void SuchThatClause::getRelationshipName(std::string& relationshipNameRef) const {
    relationshipNameRef = this->relationshipName;
}

void SuchThatClause::getRelationshipArg1(std::string& relationshipArg1Ref) const {
    relationshipArg1Ref = this->relationshipArg1;
}

void SuchThatClause::getRelationshipArg2(std::string& relationshipArg2Ref) const {
    relationshipArg2Ref = this->relationshipArg2;
}
