#pragma once

#include <string>

class ASTNode {
public:
    explicit ASTNode(const std::string& type);
    virtual ~ASTNode() = default;
    virtual std::string toString() const;
    std::string getType() const;

private:
    std::string type;
};
