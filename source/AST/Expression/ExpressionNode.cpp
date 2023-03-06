#include "ExpressionNode.h"
#include <set>

ExpressionNode::ExpressionNode(const std::string& type) : ASTNode(type) {
}

std::vector<std::string> ExpressionNode::getVariables(const std::vector<const ExpressionNode*>& expressionNodes) {
    std::set<std::string, std::less<>> resultSet;

    for (ExpressionNode const* expressionNode : expressionNodes) {
        std::vector<std::string> variables = expressionNode->getVariables();
        resultSet.insert(variables.begin(), variables.end());
    }

    std::vector<std::string> result(resultSet.begin(), resultSet.end());
    return result;
}

std::vector<std::string> ExpressionNode::getVariables() const {
    std::vector<std::string> result;
    return result;
}
