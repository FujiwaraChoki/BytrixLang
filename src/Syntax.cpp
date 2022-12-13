#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <string>

class Syntax
{
public:
    // Default constructor, do nothing once instantiated (yet)
    explicit Syntax(){};

    // Destructor
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
    std::string get_existing_variable_type(std::string var_name)
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

    // Function to check which type a variable is
    template <typename T>
    std::string get_type(T var)
    {
        // Check if var begins and ends with a " or '
        if (var[0] == '"' && var[var.size() - 1] == '"' || var[0] == '\'' && var[var.size() - 1] == '\'')
        {
            return "string";
        }
        else if (check_is_number(std::stod(var)))
        {
            return "double";
        }
        else if (check_is_number(std::stoi(var)))
        {
            return "int";
        }
        else if (var == "true" || var == "false")
        {
            return "bool";
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

        // Take out all the comments, they start with a ; and end with a ;
        std::vector<std::string> words;
        std::string word = "";
        std::string current_string = "";
        for (int i = 0; i < source_code.size(); i++)
        {
            if (source_code[i] == ';')
            {
                // We are in a comment, so we need to find the end of the comment.
                while (source_code[i] != ';')
                {
                    i++;
                }
            }
            // Check if the character is a ", if yes, then we are in a string and we need to add the character to the current string until we find another ".
            else if (source_code[i] == '"')
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

        // Search for a print statement
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] == "output")
            {
                std::string what_to_print = "";

                // Set the what_to_print variable to the next word without the ""
                what_to_print += words[i + 1].substr(1, words[i + 1].size() - 2);

                // Loop through what_to_print and check if a word begins with a $, and replace it accoringly.
                for (int j = 0; j < what_to_print.size(); j++)
                {
                    if (what_to_print[j] == '$')
                    {
                        // Get the variable name
                        std::string variable_name = "";
                        int k = j + 1;
                        while (what_to_print[k] != ' ' && k < what_to_print.size())
                        {
                            variable_name += what_to_print[k];
                            k++;
                        }

                        std::string variable_type = get_existing_variable_type(variable_name);

                        // Check if the variable exists
                        if (variable_type == "string")
                        {
                            // Replace the variable with the value of the variable
                            what_to_print.replace(j, variable_name.size() + 1, string_variables[variable_name]);
                        }
                        else if (variable_type == "double")
                        {
                            // Replace the variable with the value of the variable
                            what_to_print.replace(j, variable_name.size() + 1, std::to_string(double_variables[variable_name]));
                        }
                        else if (variable_type == "int")
                        {
                            // Replace the variable with the value of the variable
                            what_to_print.replace(j, variable_name.size() + 1, std::to_string(int_variables[variable_name]));
                        }
                        else if (variable_type == "bool")
                        {
                            // Replace the variable with the value of the variable
                            what_to_print.replace(j, variable_name.size() + 1, std::to_string(bool_variables[variable_name]));
                        }
                        else
                        {
                            // The variable does not exist.
                            throw new InvalidVariableReferenceError(variable_name);
                        }
                    }
                }

                // Print the what_to_print variable
                std::cout << what_to_print << std::endl;
            }
            else if (words[i] == "input")
            {
                // Get the prompt, which is the next word.
                std::string variable_name = "";
                std::string prompt = "";

                // Variable name is the next word
                variable_name = words[i + 1];

                // If -p was provided, then the prompt is the next word.
                if (words[i + 2] == "-p")
                {
                    prompt = words[i + 3].substr(1, words[i + 3].size() - 2);
                    // Loop through prompt and check if a word begins with a $, and replace it accoringly.
                    for (int j = 0; j < prompt.size(); j++)
                    {
                        if (prompt[j] == '$')
                        {
                            // Get the variable name
                            std::string var_name = "";
                            int k = j + 1;
                            while (prompt[k] != ' ' && prompt[k] != '\0')
                            {
                                var_name += prompt[k];
                                k++;
                            }
                            // Check if the variable is a string
                            // Call get_existing_variable_type function and assign the result to a variable
                            std::string variable_type = get_existing_variable_type(var_name);
                            if (variable_type == "string")
                            {
                                // The variable is a string
                                prompt.replace(j, var_name.size() + 1, string_variables[var_name]);
                            }
                            // Check if the variable is a double
                            else if (variable_type == "double")
                            {
                                // The variable is a double
                                prompt.replace(j, var_name.size() + 1, std::to_string(double_variables[var_name]));
                            }
                            // Check if the variable is a boolean
                            else if (variable_type == "bool")
                            {
                                // The variable is a boolean
                                if (bool_variables[var_name])
                                {
                                    prompt.replace(j, var_name.size() + 1, "true");
                                }
                                else
                                {
                                    prompt.replace(j, var_name.size() + 1, "false");
                                }
                            }
                            // Check if the variable is an integer
                            else if (variable_type == "int")
                            {
                                // The variable is an integer
                                prompt.replace(j, var_name.size() + 1, std::to_string(int_variables[var_name]));
                            }
                        }
                    }
                }

                // Check if -n was provided, if yes add a std::endl to the prompt
                bool add_new_line = false;
                if (words[i + 2] == "-n")
                {
                    add_new_line = true;
                }

                // Print the prompt only if it isn't ""
                if (prompt != "")
                {
                    if (add_new_line)
                    {
                        std::cout << prompt << std::endl;
                    }
                    else
                    {
                        std::cout << prompt;
                    }
                }

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
            else if (words[i] == "=")
            {
                std::string variable_name = words[i - 1];
                std::string variable_value = words[i + 1];

                // Check if the variable is a string
                std::string variable_type = get_existing_variable_type(variable_name);

                if (variable_type == "")
                {
                    // The variable doesn't exist, so we need to create it.
                    std::string variable_type_new = get_type(variable_value);
                    // Check what type the variable is
                    if (variable_type_new == "string")
                    {
                        // The variable is a string
                        string_variables[variable_name] = variable_value.substr(1, variable_value.size() - 2);
                    }
                    else if (variable_type_new == "double")
                    {
                        // The variable is a double
                        double_variables[variable_name] = std::stod(variable_value);
                    }
                    else if (variable_type_new == "int")
                    {
                        // The variable is an integer
                        int_variables[variable_name] = std::stoi(variable_value);
                    }
                    else if (variable_value == "true" || variable_value == "false")
                    {
                        bool_variables[variable_name] = (variable_value == "true");
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

        // Print out all bool variables.
        for (auto it = bool_variables.begin(); it != bool_variables.end(); it++)
        {
            std::cout << it->first << " = " << it->second << std::endl;
        }
    }
};