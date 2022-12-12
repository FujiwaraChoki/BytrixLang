/*
The Interpreter for the Bytrix programming language
*/
#include <iostream>
#include <fstream>
#include <string>
#include "BytrixExceptions.h"
#include "Syntax.cpp"

bool check_file(std::string file_name)
{
	// Check if file ends with .btx
	if (file_name.substr(file_name.find_last_of(".") + 1) != "btx")
	{
		throw InvalidFileTypeError(file_name);
		return false;
	}

	std::ifstream file(file_name);
	return file.good();
}

std::string get_file_contents(std::string file_name)
{
	std::string contents;
	std::ifstream file(file_name);
	std::string line;
	while (std::getline(file, line))
	{
		contents += line;
		contents.push_back('\n');
	}
	return contents;
}

int main(int argc, const char **args)
{
	Syntax syntax;
	std::string file_name = args[1];
	bool file_exists = check_file(file_name);
	if (file_exists == false)
	{
		throw FileNotFoundError(file_name);
		return 0;
	}
	std::string source_code = get_file_contents(file_name);

	// Parse the source code
	syntax.parse(source_code);

	// Print all variables
	//syntax.print_variables();
	return 0;
}