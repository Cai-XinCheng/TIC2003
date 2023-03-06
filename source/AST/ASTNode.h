#pragma once

#include <string>

class ASTNode {
public:
    explicit ASTNode(const std::string& type);
    virtual std::string toString() const;
    std::string getType() const;
protected:
    virtual ~ASTNode() = default;

private:
    std::string type;
};
