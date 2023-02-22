#include "Declaration.h"

Declaration::Declaration(const std::string& designEntity, const std::vector<std::string>& synonyms)
    : ASTNode("Declaration"), designEntity(designEntity), synonyms(synonyms) {
}

void Declaration::getDesignEntity(std::string& designEntityRef) const {
    designEntityRef = this->designEntity;
}

void Declaration::getSynonyms(std::vector<std::string>& synonymsRef) const {
    synonymsRef = this->synonyms;
}
