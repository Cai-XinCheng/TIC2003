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
