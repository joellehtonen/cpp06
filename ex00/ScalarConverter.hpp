#pragma once
#include <string>
#include <iostream>

class ScalarConverter {
	private:
		//CONSTRUCTORS
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter& operator=(const ScalarConverter& copy);

		//HELPER FUNCTIONS
		static bool	isChar(const std::string& literal);
		static bool	isInt(const std::string& literal);
		static bool	isFloat(const std::string& literal, bool& boolDouble);
		//static bool	isDouble(const std::string& literal);


	public:
		static void	convert(std::string literal);
};