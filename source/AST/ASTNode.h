#pragma once

#include <string>

class ASTNode {
public:
    explicit ASTNode(const std::string& type);
    void getType(std::string& typeRef) const;

private:
    std::string type;
};
