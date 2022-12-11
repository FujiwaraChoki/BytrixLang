/*Bytrix Notification NameSpace*/
#include <iostream>
#include <string>

namespace BytrixNot
{
	void Error(std::string message)
	{
		// Print out the error message in red, and concatenate the message with the default color
		printf("\033[1;31m%s\033[0m", message.c_str());
	}

	void Warning(std::string message)
	{
		// Print out the warning message in yellow, and concatenate the message with the default color
		printf("\033[1;33m%s\033[0m", message.c_str());
	}

	void Success(std::string message)
	{
		// Print out the success message in green, and concatenate the message with the default color
		printf("\033[1;32m%s\033[0m", message.c_str());
	}

	void Info(std::string message)
	{
		// Print out the info message in blue, and concatenate the message with the default color
		printf("\033[1;34m%s\033[0m", message.c_str());
	}
}