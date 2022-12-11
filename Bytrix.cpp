/*
The Interpreter for the Bytrix programming language
*/
#include <iostream>
#include <fstream>
#include <string>
#include "BytrixExceptions.h"

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
	std::ifstream file(file_name);
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return contents.c_str();
}

int main(int argc, const char **args)
{
	std::string file_name = args[1];
	bool file_exists = check_file(file_name);
	if (file_exists == false)
	{
		throw FileNotFoundError(file_name);
		return 0;
	}
	std::string source_code = get_file_contents(file_name);
	BytrixNot::Success("Here are the file contents: ");
	std::cout << source_code << "\n";

	return 0;
}