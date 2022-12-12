#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <string>

class Syntax
{
    // This class is used to store the syntax of a language.
    // It is used to check if a given string is valid syntax.
    // It is also used to check if a given string is valid syntax for a given language.

public:
    // The constructor for the Syntax class.
    explicit Syntax(){}; // This is the default constructor.

    // The destructor for the Syntax class.
    ~Syntax(){};

    std::vector<std::string> syntax = {"for", "while", "if", "else", "elif", "switch", "case", "break", "continue", "return", "print", "this", "true", "false"};

    // Map of the string variables
    std::map<std::string, std::string> string_variables;

    // Map of the number variables
    std::map<std::string, double> double_variables;

    // Map of the boolean variables
    std::map<std::string, bool> bool_variables;

    // Map of integer variables
    std::map<std::string, int> int_variables;

    template <typename T>
    bool check_is_number(T arg)
    {
        // Check if the argument is a number.
        if (std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, long>::value || std::is_same<T, long long>::value || std::is_same<T, short>::value || std::is_same<T, long double>::value)
        {
            return true;
        }
        return false;
    }

    // Function to check whether a given string is a variable
    std::string check_is_variable(std::string var_name)
    {
        // Check if the variable is a string variable
        if (string_variables.find(var_name) != string_variables.end())
        {
            return "string";
        }
        else if (double_variables.find(var_name) != double_variables.end())
        {
            return "double";
        }
        else if (bool_variables.find(var_name) != bool_variables.end())
        {
            return "bool";
        }
        else if (int_variables.find(var_name) != int_variables.end())
        {
            return "int";
        }
        else
        {
            return "";
        }
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
                    std::string what_to_print = "";

                    // Set the what_to_print variable to the next word without the ""
                    what_to_print = words[i + 1].substr(1, words[i + 1].size() - 2);

                    // Check if next word is a variable
                    if (words[i + 2][0] == '$')
                    {
                        std::string var_name = words[i + 2].substr(1, words[i + 2].size() - 1);
                        // Check if the variable is a string
                        // Call check_is_variable function and assign the result to a variable
                        std::string variable_type = check_is_variable(var_name);
                        if (variable_type == "string")
                        {
                            // The variable is a string
                            what_to_print += string_variables[var_name];
                        }
                        // Check if the variable is a double
                        else if (variable_type == "double")
                        {
                            // The variable is a double
                            what_to_print += std::to_string(double_variables[var_name]);
                        }
                        // Check if the variable is a boolean
                        else if (variable_type == "bool")
                        {
                            // The variable is a boolean
                            if (bool_variables[words[i + 2]])
                            {
                                what_to_print += "true";
                            }
                            else
                            {
                                what_to_print += "false";
                            }
                        }
                        // Check if the variable is an integer
                        else if (variable_type == "int")
                        {
                            // The variable is an integer
                            what_to_print += std::to_string(int_variables[var_name]);
                        }
                        else
                        {
                            // Throw Undefined variable error
                            throw new UndefinedVariableError(var_name);
                        }
                    }
                    else
                    {
                        // The next word is a string
                        what_to_print = words[i + 1].substr(1, words[i + 1].size() - 2);
                    }
                    std::cout << what_to_print << std::endl;
                }
                else if (words[i] == "input")
                {
                    // Get the prompt, which is the next word.
                    std::string prompt = words[i + 1].substr(1, words[i + 1].size() - 2);
                    // Get the variable name, which is the word after the prompt.
                    std::string variable_name = words[i + 2];

                    // Print the prompt.
                    std::cout << prompt << std::endl;

                    // Get the input.
                    std::string input;
                    std::cin >> input;

                    // Check if the input is a number.
                    if (check_is_number(input))
                    {
                        // The input is a number, so we need to convert it to a number.
                        // Check if the input is an integer.
                        if (input.find('.') == std::string::npos)
                        {
                            // The input is an integer.
                            int input_int = std::stoi(input);
                            int_variables[variable_name] = input_int;
                        }
                        else
                        {
                            // The input is a double.
                            double_variables[variable_name] = std::stod(input);
                        }
                    }
                    else
                    {
                        // Store string in memory
                        string_variables[variable_name] = input;
                    }
                }
            }
        }
    }

    // Print out all variables.
    void print_variables()
    {
        // Print out all string variables.
        for (auto it = string_variables.begin(); it != string_variables.end(); it++)
        {
            std::cout << it->first << " = " << it->second << std::endl;
        }

        // Print out all double variables.
        for (auto it = double_variables.begin(); it != double_variables.end(); it++)
        {
            std::cout << it->first << " = " << it->second << std::endl;
        }

        // Print out all int variables.
        for (auto it = int_variables.begin(); it != int_variables.end(); it++)
        {
            std::cout << it->first << " = " << it->second << std::endl;
        }
    }
};