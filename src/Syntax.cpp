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
    ~Syntax(){};

    std::vector<std::string> syntax = {"for", "while", "if", "else", "elif", "switch", "case", "break", "continue", "return", "print", "this", "true", "false"};

    bool checkKeyword(std::string keyword)
    {
        for (int i = 0; i < this->syntax.size(); i++)
        {
            if (keyword == syntax[i])
            {
                return true;
            }
        }
        return false;
    }

    void parse(std::string source_code)
    {
        // This function is used to parse the source code.
        // Split the source code into words (seperated by space).
        std::vector<std::string> words;
        std::string word = "";
        std::string current_string = "";
        for (int i = 0; i < source_code.size(); i++)
        {
            // Check if the character is a ", if yes, then we are in a string and we need to add the character to the current string until we find another ".
            if (source_code[i] == '"')
            {
                // Check if the current string is empty, if yes, then we are starting a string.
                if (current_string == "")
                {
                    current_string = "\"";
                }
                else
                {
                    // We are ending a string.
                    current_string += "\"";
                    words.push_back(current_string);
                    current_string = "";
                }
            }
            else if (source_code[i] == ' ' || source_code[i] == '\n')
            {
                // Check if the current string is empty, if yes, then we are not in a string.
                if (current_string == "")
                {
                    // Check if the word is not empty, if yes, then add the word to the words vector.
                    if (word != "")
                    {
                        words.push_back(word);
                        word = "";
                    }
                }
                else
                {
                    // We are in a string, so add the character to the current string.
                    current_string += source_code[i];
                }
            }
            else
            {
                // Check if the current string is empty, if yes, then we are not in a string.
                if (current_string == "")
                {
                    // We are not in a string, so add the character to the word.
                    word += source_code[i];
                }
                else
                {
                    // We are in a string, so add the character to the current string.
                    current_string += source_code[i];
                }
            }
        }

        // Now, we need to check if the words are valid syntax.
        if (words[0] == "main:")
        {
            // Check if the last word is "end"
            // Search for a print statement
            for (int i = 0; i < words.size(); i++)
            {
                if (words[i] == "print")
                {
                    //std::cout << "Found a print statement!" << std::endl;

                    // Check if the next word is a string
                    if (words[i + 1][0] == '"' && words[i + 1][words[i + 1].size() - 1] == '"')
                    {
                        // Print next word without ""
                        std::cout << words[i + 1].substr(1, words[i + 1].size() - 2) << std::endl;
                    }
                    else
                    {
                        throw InvalidStringError(words[i + 1]);
                    }
                }
            }
        }
    }
};