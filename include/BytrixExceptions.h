#pragma once
#include "../include/BytrixNot.h"
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

/*Why am I getting error, that BytrixNot::Error was already defined?*/