#include "ExpNode.h"
#include <format>
#include <string>


std::string ExpNode::toString() const {
    std::string res = std::format("{}", lhs->toString());
    if (rhs != NULL) {
        res = std::format("({})", lhs->toString());
        res += std::format(" {} ", operate);
        res += std::format("({})", rhs->toString());
    }
    return res;
}


std::string VarNode::toString() const {
    return std::format("{}", variableName);
}

std::string ConstNode::toString() const {
    return std::format("{}", std::to_string(value));
}
