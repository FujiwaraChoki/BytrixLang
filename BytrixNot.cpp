/*Bytrix Notification NameSpace*/
#include <iostream>


namespace BytrixNot {
	// Error message (with Red)
	template <typename T>
	void Error(T message) {
		std::cout << "\033[1;31m" << message << "\033[0m" << std::endl;
	}
	
	template <typename T>
	void Warning(T message) {
		std::cout << "\033[1;33m" << message << "\033[0m" << std::endl;
	}

	template <typename T>
	void Success(T message) {
		std::cout << "\033[1;32m" << message << "\033[0m" << std::endl;
	}
	
	template <typename T>
	void Info(T message) {
		std::cout << "\033[1;34m" << message << "\033[0m" << std::endl;
	}
}