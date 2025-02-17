#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <exception> //for std::exception
#include <iomanip> //for setprecision
#include <climits> //for int_max and int_min

class ScalarConverter {
	private:
		//CONSTRUCTORS
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter& operator=(const ScalarConverter& copy);

		//HELPER FUNCTIONS
		static void	isFloatDouble(const std::string& literal, bool& somethingFound, bool& foundFloat, bool& foundDouble, int& decimalCount);
		static void	isInt(const std::string& literal, bool& somethingFound, bool& foundInt);
		static void	isChar(const std::string& literal, bool& somethingFound, bool& foundChar);
		static void isException(const std::string& literal, std::string& exceptionType);
		static void		handleExceptions(const std::string& exceptionType, int& literalInt, float& literalFloat, double& literalDouble);
		static double	makeDouble(const std::string& literal, std::string& exceptionType);
		static float	makeFloat(const std::string& literal, std::string& exceptionType);
		static int		makeInt(const std::string& literal, std::string& exceptionType);
		static char		makeChar(const std::string& literal, std::string& exceptionType);
		static void		checkLimits(const double& check, std::string& exceptionType);
		static void	convertFromChar(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble);
		static void	convertFromInt(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble);
		static void	convertFromFloat(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble);
		static void	convertFromDouble(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble);
		static void		printLiterals(const char& literalChar, const int& literalInt, const float& literalFloat, const double& literalDouble, const std::string& exceptionType, int& decimalCount, bool& foundInt);

	public:
		static void	convert(std::string literal);
};
