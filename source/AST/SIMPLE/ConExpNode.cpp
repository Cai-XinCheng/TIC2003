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


std::vector<std::string> ConExpNode::getVariables() const {
    return ExpressionNode::getVariables({ lhs, rhs });
}

std::vector<int64_t> ConExpNode::getConstants() const {
    return ExpressionNode::getConstants({ lhs, rhs });
}
