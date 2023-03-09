#include "ConExpNode.h"
#include <format>

const std::string& ConExpNode::type = "conExp";

ConExpNode::ConExpNode(const std::string& operate, const ExpressionNode* lhs, const ExpressionNode* rhs)
    : ExpressionNode(type), operate(operate), lhs(lhs), rhs(rhs) {
}

ConExpNode::~ConExpNode() {
    delete lhs;
    delete rhs;
}

std::string ConExpNode::toString() const {
    return std::format("{} {} {}", lhs->toString(), operate, rhs->toString());
}
