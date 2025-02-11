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

void ScalarConverter::convert(std::string literal) {
	//* first detect literal type

	//how to differentiate int 1 and char 1?
	// assume that if number, then int
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
};