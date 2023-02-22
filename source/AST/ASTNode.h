#pragma once

#include <string>

class ASTNode {
public:
    explicit ASTNode(const std::string& type);
    std::string getType() const;

private:
    std::string type;
};
