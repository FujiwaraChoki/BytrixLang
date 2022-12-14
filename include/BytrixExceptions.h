#include "BytrixNot.h"
#include <stdio.h>
#include <string>

class FileNotFoundError
{
public:
	FileNotFoundError(std::string file_name)
	{
		BytrixNot::Error("FileNotFoundError: " + file_name + " does not exist.");
	}
};

class FileNotReadableError
{
public:
	FileNotReadableError(std::string file_name)
	{
		BytrixNot::Error("FileNotReadableError: " + file_name + " is not readable.");
	}
};

class InvalidFileTypeError
{
public:
	InvalidFileTypeError(std::string file_name)
	{
		BytrixNot::Error("InvalidFileTypeError: " + file_name + " is not a Bytrix (.btx) file.");
	}
};

class InvalidStringError
{
public:
	InvalidStringError(std::string string)
	{
		BytrixNot::Error("InvalidStringError: " + string + " is not a valid string.");
	}
};

class UndefinedVariableError
{
public:
	UndefinedVariableError(std::string variable)
	{
		BytrixNot::Error("UndefinedVariableError: " + variable + " is not defined.");
	}
};

class InvalidVariableReferenceError
{
public:
	InvalidVariableReferenceError(std::string variable)
	{
		BytrixNot::Error("InvalidVariableReferenceError: " + variable + " is not a valid variable.");
	}
};

class UndefinedFunctionError
{
public:
	UndefinedFunctionError(std::string function)
	{
		BytrixNot::Error("UndefinedFunctionError: " + function + " is not defined.");
	}
};