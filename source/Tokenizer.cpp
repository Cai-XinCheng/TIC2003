#include "Tokenizer.h"
#include <iostream>
#include <set>
#include <regex>

// constructor
Tokenizer::Tokenizer() {}

// destructor
Tokenizer::~Tokenizer() {}

const std::set<char> Tokenizer::independentPunctuations({ ';', '{', '}', '(', ')', ',' });

// method to tokenize a program / query string
// it currently tokenizes the string into a vector of 
// words (any alphanumeric sequence of characters starting with a letter, e.g., "num1"),
// numbers (any numeric sequence of characters, e.g., "1001"),
// and punctuations (any other non-space characters, e.g., "=", ";", "{", "}").
// it should be extended as needed to handle additional SIMPLE / PQL grammar rules.
void Tokenizer::tokenize(std::string text, std::vector<std::string>& tokens) {
    tokens.clear();
    std::string token;

    unsigned int i = 0;
    while (i < text.length()) {
        char ch = text.at(i);

        if (isdigit(ch)) { // scan for a numeric sequence
            token.push_back(ch);
            i++;

            while (i < text.length()) {
                ch = text.at(i);
                if (isdigit(ch)) {
                    token.push_back(ch);
                    i++;
                }
                else {
                    break;
                }
            }

            tokens.push_back(token);
            token.clear();
        }
        else if (isalpha(ch)) { // scan for an alphanumeric sequence starting with a letter 
            token.push_back(ch);
            i++;
           
            while (i < text.length()) {
                ch = text.at(i);
                if (isalnum(ch)) {
                    token.push_back(ch);
                    i++;
                }
                else if (ch == '*') { // scan for Next*, Parent*, Calls* etc...
                    std::string content = token + text.substr(i);
                    std::regex function_pattern(R"(^[A-Za-z][A-Za-z0-9]*\*?\s*?\(\s*("[^"]*?"|[A-Za-z][A-Za-z0-9]*|\d+|_)(\s*,\s*("[^"]*?"|[A-Za-z][A-Za-z0-9]*|\d+|_))*\s*\))");
                    if (std::regex_search(content, function_pattern)) {
                        token.push_back(ch);
                        i++;
                    }
                    break;
                }
                else {
                    break;
                }
            }

            tokens.push_back(token); 
            token.clear();
        }
        else if (ch == '"') { // scan for string sequence starting with " and ending with "
            token.push_back(ch);
            i++;

            while (i < text.length()) {
                ch = text.at(i);
                token.push_back(ch);
                i++;
                if (ch == '"') {
                    break;
                }
            }

            tokens.push_back(token);
            token.clear();
        }
        else if (ch == '_') { // scan for placeholder sequence starting with _
            token.push_back(ch);
            i++;

            if (i < text.length()) {
                ch = text.at(i);
                if (ch == '"') {
                    token.push_back(text.at(i));
                    i++;
                    while (i < text.length()) {
                        ch = text.at(i);
                        token.push_back(ch);
                        i++;
                        if (ch == '"') {
                            break;
                        }
                    }
                    if (i < text.length()) {
                        ch = text.at(i);
                        if (ch == '_') {
                            token.push_back(text.at(i));
                            i++;
                        }
                    }
                }
            }

            tokens.push_back(token);
            token.clear();
        }
        else if (!isspace(ch)) { // scan for punctuations
            token.push_back(ch);
            i++;

            if (!independentPunctuations.contains(ch)) { // scan for multi-character operators
                while (i < text.length()) {
                    ch = text.at(i);
                    if (ispunct(ch) && !independentPunctuations.contains(ch)) {
                        token.push_back(ch);
                        i++;
                    }
                    else {
                        break;
                    }
                }
            }

            tokens.push_back(token);
            token.clear();
        }
        else {
            i++;
        }
    }
}
