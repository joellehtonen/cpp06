#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <exception>

class ScalarConverter {
	private:
		//CONSTRUCTORS
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter& operator=(const ScalarConverter& copy);

		//HELPER FUNCTIONS
		static void	isFloatDouble(const std::string& literal, bool* somethingFound, bool* foundFloat, bool* foundDouble);
		static void	isInt(const std::string& literal, bool* somethingFound, bool* foundInt);
		static void	isChar(const std::string& literal, bool* somethingFound, bool* foundChar);
		static void isException(const std::string& literal, std::string* exceptionType);
		static void		handleException();
		static double	makeDouble(const std::string& literal);
		static float	makeFloat(const std::string& literal);
		static int		makeInt(const std::string& literal);
		static char		makeChar(const std::string& literal, std::string *exceptionType);
		static void		convertFromChar(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble);
		static void		convertFromInt(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble);
		static void		convertFromFloat(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble);
		static void		convertFromDouble(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble);
		static void		printLiterals(const char& literalChar, const int& literalInt, const float& literalFloat, const double& literalDouble, const std::string* exceptionType);

	public:
		static void	convert(std::string literal);
};