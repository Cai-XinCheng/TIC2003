#pragma once

#include "SuchThatClause.h"
#include <string>

SuchThatClause::SuchThatClause(const std::string& relationshipName, const std::string& relationshipArg1, const std::string& relationshipArg2)
    : FilterClause("SuchThatClause"), relationshipName(relationshipName), relationshipArg1(relationshipArg1), relationshipArg2(relationshipArg2) {
}

std::string SuchThatClause::getRelationshipName() const {
    return this->relationshipName;
}

std::string SuchThatClause::getRelationshipArg1() const {
    return this->relationshipArg1;
}

std::string SuchThatClause::getRelationshipArg2() const {
    return this->relationshipArg2;
}
