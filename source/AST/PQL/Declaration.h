#pragma once

#include "../ASTNode.h"
#include <string>
#include <vector>

class Declaration : public ASTNode {
public:
    explicit Declaration(const std::string& designEntity, const std::vector<std::string>& synonyms);
    std::string toString() const override;
    std::string getDesignEntity() const;
    std::vector<std::string> getSynonyms() const;

private:
    std::string designEntity;
    std::vector<std::string> synonyms;
};
