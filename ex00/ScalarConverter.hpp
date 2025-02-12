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

		//VARIABLES
		static bool foundChar;
		static bool foundInt;
		static bool foundFloat;
		static bool foundDouble;
		static std::string exceptionType;

		//HELPER FUNCTIONS
		static bool nothingFound();
		static void	isFloatDouble(const std::string& literal);
		static void	isInt(const std::string& literal);
		static void	isChar(const std::string& literal);
		static void isException(const std::string& literal);
		static void		handleException();
		static void		handleChar(const std::string& literal);
		static void		handleInt(const std::string& literal);
		static void		handleFloat(const std::string& literal);
		static void		handleDouble(const std::string& literal);
		static double	makeDouble(const std::string& literal);
		static float	makeFloat(const std::string& literal);
		static int		makeInt(const std::string& literal);
		static char		makeChar(const std::string& literal);
		static std::string makeString(const std::string& literal);

	public:
		static void	convert(std::string literal);
};