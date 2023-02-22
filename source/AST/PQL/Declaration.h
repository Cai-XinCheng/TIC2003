#pragma once

#include "../ASTNode.h"
#include <string>
#include <vector>

class Declaration : public ASTNode {
public:
    explicit Declaration(const std::string& designEntity, const std::vector<std::string>& synonyms);
    void getDesignEntity(std::string& designEntityRef) const;
    void getSynonyms(std::vector<std::string>& synonymsRef) const;

private:
    std::string designEntity;
    std::vector<std::string> synonyms;
};
