#include "ASTNode.h"
#include <stack>

int priority(char c);

ASTNode::ASTNode(const std::string& type) : type(type) {
}

std::string ASTNode::toString() const {
    return this->type;
}

std::string ASTNode::getType() const {
    return this->type;
}

std::string ASTNode::toPostfix(std::string expression) {
    // a stack to store operators
    std::stack<char> stack;
    std::string output = "";
    for (char c : expression) {
        if (isalnum(c)) {
            output += c;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            // print out all operators in stack until '('
            while (stack.top() != '(') {
                output += stack.top();
                stack.pop();
            }
        }
        else { // operator: +, -, *, /, %
            // if the read operator has higher priority than the top of stack
            if (priority(c) > priority(stack.top())) {
                stack.push(c);
            }
            else {
                output += stack.top();
                stack.pop();
                stack.push(c);
            }
        }
    }
    while (!stack.empty()) {
        output += stack.top();
        stack.pop();
    }
    return output;
}

// define the priority level of operators
int priority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    else if (c == '*' || c == '/' || c == '%') {
        return 2;
    }
    else {
        return 0;
    }
}
