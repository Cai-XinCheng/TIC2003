#include "Declaration.h"

Declaration::Declaration(const std::string& designEntity, const std::vector<std::string>& synonyms)
    : ASTNode("Declaration"), designEntity(designEntity), synonyms(synonyms) {
}

std::string Declaration::getDesignEntity() const {
    return this->designEntity;
}

std::vector<std::string> Declaration::getSynonyms() const {
    return this->synonyms;
}
