#include "Declaration.h"
#include <format>
#include <numeric>

const std::string& Declaration::nodeType = "Declaration";

Declaration::Declaration(const std::string& designEntity, const std::vector<std::string>& synonyms)
    : ASTNode(nodeType), designEntity(designEntity), synonyms(synonyms) {
}

std::string Declaration::toString() const {    
    std::string commaSeparatedSynonyms = std::accumulate(synonyms.begin(), synonyms.end(), std::string(),
        [](std::string const& acc, std::string const& element) {
            return !acc.empty() ? acc + ", " + element : element;
        });
    return std::format("{} {};", designEntity, commaSeparatedSynonyms);
}

std::string Declaration::getDesignEntity() const {
    return this->designEntity;
}

std::vector<std::string> Declaration::getSynonyms() const {
    return this->synonyms;
}
