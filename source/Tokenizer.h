#pragma once

#include <string>
#include <set>
#include <vector>

// A class to tokenize a program / query string into a vector of tokens
class Tokenizer {

public:
    // default constructor
    Tokenizer();

    // destructor
    ~Tokenizer();

    // method for tokenizing a program / query string
    void tokenize(std::string text, std::vector<std::string>& tokens);

private:
    static std::set<char> independentPunctuations;
};

