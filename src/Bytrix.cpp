/*
The Interpreter for the Bytrix programming language
Author: Sami Hindi
Version: 0.0.1
*/
#include <iostream>
#include <fstream>
#include <string>
#include "../include/BytrixExceptions.h"
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
	BytrixNot::Info("Bytrix Interpreter v0.0.1");
	Syntax syntax;
	std::string source_code;
	std::string file_name = args[1];
	bool file_exists = check_file(file_name);
	if (file_exists == false)
	{
		throw FileNotFoundError(file_name);
		return 0;
	}
	source_code = get_file_contents(file_name);

	// Remove the comments from source_code, they start with /* and end with */,
	// if /* and */ were found in the source code
	if (source_code.find("/*") != std::string::npos && source_code.find("*/") != std::string::npos)
	{
		// Remove the comments from source_code
		source_code.erase(source_code.find("/*"), source_code.find("*/") - source_code.find("/*") + 2);
	}

	// Parse the source code
	syntax.parse(source_code);

	// Print all variables
	//syntax.print_variables();

	return 0;
}