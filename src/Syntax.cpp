#include <string>
#include <iostream>
#include <vector>

class Syntax
{
    // This class is used to store the syntax of a language.
    // It is used to check if a given string is valid syntax.
    // It is also used to check if a given string is valid syntax for a given language.

public:
    // The constructor for the Syntax class.
    Syntax(){}; // This is the default constructor.

    // The destructor for the Syntax class.
    ~Syntax();

    bool checkKeyword(std::string keyword)
    {
        for (int i = 0; i < syntax.size(); i++)
        {
            if (keyword == syntax[i])
            {
                return true;
            }
        }
        return false;
    }

private:
    std::vector<std::string> syntax = {"for", "while", "if", "else", "elif", "switch", "case", "break", "continue", "return", "print", "this", "true", "false"};
};