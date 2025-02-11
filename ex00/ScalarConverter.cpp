#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
	std::cout << "ScalarConverter constructor called" << std::endl;
};

ScalarConverter::~ScalarConverter() {
	std::cout << "ScalarConverter deconstructor called" << std::endl;
};

ScalarConverter::ScalarConverter(const ScalarConverter& copy) {
	(void)copy;
	std::cout << "ScalarConverter copy constructor called" << std::endl;
};

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& copy) { 
	(void)copy;
	std::cout << "ScalarConverter copy assignment constructor called" << std::endl;
	return *this;
};

bool ScalarConverter::isFloat(const std::string& literal, bool& boolDouble) { 

	// check if there is a period
	size_t periodPosition = literal.find('.');
	if (periodPosition == std::string::npos)
		return false;
	
	// check if every digit BEFORE '.' is a number
	for (int i = periodPosition - 1; i >= 0; i--)
	{
		if (literal[i] < 48 || literal[i] > 57)
			return false;
	}

	// check if every digit (except the last) AFTER '.' is a number
	size_t len = literal.length();
	for (int i = periodPosition + 1; i <= len - periodPosition - 1; i++)
	{
		if (literal[i] < 48 || literal[i] > 57)
			return false;
	}

	// check if last char is 'f'. if last char is number instead, flip double bool
	if (literal[len] != 'f')
	{
		if (literal[len] >= 48 && literal[len] <= 57)
			boolDouble = true;
		return false;
	}

	return true;
};

// bool ScalarConverter::isChar(std::string literal)
// {
// 	for (int i; i = 0; i <= literal.length())
// 	{
// 		if (literal[i] >= 33 && literal[i] <= 126)
// 		return (true);
// 	}
// 	// handle strings too
// };



void ScalarConverter::convert(std::string literal) {
	bool boolDouble = false;
	bool boolFloat = isFloat(literal, &boolDouble);
	bool boolInt;
	bool boolChar;

	// isFloatDouble(literal, boolFloat, boolDouble);
	// isInt(literal, boolInt);
	// isChar(literal, boolChar);
	//handle strings by checking these in this order, and if more than one = true, then flag as false input (= not literal)



	//* first detect literal type

	//how to differentiate int 1 and char 1?
	// assume that if number, then int? or both valid same time?
	// if (number).(number)f then float
	// if (number).(number) then double





	//* then convert from string to actual type
	//* then convert to three other types EXPLICITLY
		//those being char, int, float, double
	//* then print all four


	//print char
		//TODO convert numbers into ascii
	//print int
	//print float
	//print double

	//TODO handle nan, nanf, -inff, +inff
	//TODO handle conversions that dont make sense, overflows
	//TODO print messages for these ("impossible"?)
	//? which headers handle numeric limits and special values
	//! what if many literals in one string
};