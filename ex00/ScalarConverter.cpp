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
	bool		foundDouble = false;
	bool		foundFloat = false;
	bool		foundInt = false;
	bool		foundChar = false;
	bool		somethingFound = false;
	std::string	exceptionType = "";

	if (literal.length() == 0)
		throw std::invalid_argument("Argument cannot be empty");

	isFloatDouble(literal, &somethingFound, &foundFloat, &foundDouble);
	if (somethingFound == false)
		isInt(literal, &somethingFound, &foundInt);
	if (somethingFound == false)
		isChar(literal, &somethingFound, &foundChar);
	if (somethingFound == false)
		isException(literal, &exceptionType);
	if (somethingFound == false && exceptionType == "")
		throw std::invalid_argument("Argument is not a literal");

	std::cout << "boolchar = " << foundChar << std::endl;
	std::cout << "boolint = " << foundInt << std::endl;
	std::cout << "boolfloat = " << foundFloat << std::endl;
	std::cout << "booldouble = " << foundDouble << std::endl;
	std::cout << "boolexception = " << exceptionType << std::endl;

	char	literalChar = '0';
	int		literalInt = 0;
	float	literalFloat = 0.0f;
	double	literalDouble = 0.0; 

	if (foundChar == true)
	{
		literalChar = makeChar(literal);
		convertFromChar(&literalChar, &literalInt, &literalFloat, &literalDouble);
	}
	else if (foundInt == true)
	{
		literalInt = makeInt(literal);
		convertFromInt(&literalChar, &literalInt, &literalFloat, &literalDouble);
	}
	else if (foundFloat == true)
	{
		literalFloat = makeFloat(literal);
		convertFromFloat(&literalChar, &literalInt, &literalFloat, &literalDouble);
	}
	else if (foundDouble == true)
	{
		literalDouble = makeDouble(literal);
		convertFromDouble(&literalChar, &literalInt, &literalFloat, &literalDouble);
	}
	if (exceptionType != "")
		handleException();

	printLiterals(&literalChar, &literalInt, &literalFloat, &literalDouble, &exceptionType);
	//TODO handle conversions that dont make sense, overflows
	//TODO print messages for these ("impossible"?)
	//? which headers handle numeric limits and special values
};

// checks if the literal type is float or double
//! test with 1.f and 1.
void ScalarConverter::isFloatDouble(const std::string& literal, bool* somethingFound, bool* foundFloat, bool* foundDouble) { 

	size_t periodPosition	= literal.find('.');
	size_t len 				= literal.length() - 1;

	// check if there is a period
	if (periodPosition == std::string::npos)
		return ;

	// check if every char BEFORE '.' is a number
	for (int i = periodPosition - 1; i >= 0; i--)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
	}

	// check if every char (except the last) AFTER '.' is a number
	for (size_t i = periodPosition + 1; i < len; i++)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
	}

	// check if last char is 'f'. if last char is number, flip double bool
	if (literal[len] != 'f') //&& literal[len] != 'F')
	{
		if (std::isdigit(static_cast<unsigned char>(literal[len])) == true || literal[len] == '.')
		{
			*somethingFound = true;
			*foundDouble = true;
		}
		return ;
	}
	*somethingFound = true;
	*foundFloat = true;
	return ;
};

// checks if the literal type is int
//? check for signs?
void ScalarConverter::isInt(const std::string& literal, bool* somethingFound, bool* foundInt)
{
	size_t len = literal.length() - 1;
	for (size_t i = 0; i <= len; i++)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
	}
	*somethingFound = true;
	*foundInt = true;
	return ;
}

// checks if the literal type is char
void ScalarConverter::isChar(const std::string& literal, bool* somethingFound, bool* foundChar)
{
	size_t len = literal.length();
	if (len != 1)
		return ;
	if (std::isprint(static_cast<unsigned char>(literal[0])) == false)
		return ;
	*somethingFound = true;
	*foundChar = true;
	return ;
};

void ScalarConverter::isException(const std::string& literal, std::string* exceptionType)
{
	if (literal == "nan" || literal == "nanf")
		*exceptionType = "nan";
	else if (literal == "+inf" || literal == "+inff")
		*exceptionType = "+inf";
	else if (literal == "-inf" || literal == "-inff")
		*exceptionType = "-inf";
	return ;
};

double ScalarConverter::makeDouble(const std::string& literal) {
	return (std::stod(literal));
};

float ScalarConverter::makeFloat(const std::string& literal) {
	return (std::stof(literal));
};

int ScalarConverter::makeInt(const std::string& literal) {
	return (std::stoi(literal));
};

char ScalarConverter::makeChar(const std::string& literal, std::string* exceptionType) {
	unsigned int	asInteger = stoi(literal);
	if (asInteger < 32 || asInteger	> 126)
	{
		*exceptionType = "non-printable";
		return (static_cast<char>(0));
	}
	return static_cast<char>(asInteger);
};

// can be done? or alt approach?
void ScalarConverter::convertFromChar(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble) {
	*literalInt = static_cast<int>(*literalChar);
	*literalFloat= static_cast<float>(*literalChar);
	*literalDouble = static_cast<double>(*literalChar);
};

void ScalarConverter::convertFromInt(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble) {
	*literalChar = static_cast<char>(*literalInt);
	*literalFloat= static_cast<float>(*literalInt);
	*literalDouble = static_cast<double>(*literalInt);
};

void ScalarConverter::convertFromFloat(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble) {
	*literalChar = static_cast<char>(*literalFloat);
	*literalInt = static_cast<int>(*literalFloat);
	*literalDouble = static_cast<double>(*literalFloat);
};

void ScalarConverter::convertFromDouble(char* literalChar, int* literalInt, float* literalFloat, double* literalDouble) {
	*literalChar = static_cast<char>(*literalDouble);
	*literalInt = static_cast<int>(*literalDouble);
	*literalFloat = static_cast<float>(*literalDouble);
};

void ScalarConverter::printLiterals(const char& literalChar, const int& literalInt, const float& literalFloat, const double& literalDouble, const std::string* exceptionType) 
{
	if (*exceptionType == "")
	{
		std::cout << "char: " << literalChar << std::endl;
		std::cout << "int: " << literalInt << std::endl;
		std::cout << "float: " << literalFloat << "f" << std::endl;
		std::cout << "double: " << literalDouble << std::endl;
	}
	else if (*exceptionType == "non-printable")
	{
		std::cout << "char: non-printable" << std::endl;
		std::cout << "int: " << literalInt << std::endl;
		std::cout << "float: " << literalFloat << "f" << std::endl;
		std::cout << "double: " << literalDouble << std::endl;
	}
	else if (*exceptionType == "nan")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nan" << "f" << std::endl; //!Maybe these should be proper values within variables?
		std::cout << "double: nan" << std::endl;
	}
	else if (*exceptionType == "+inf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: " << std::endl;
		std::cout << "float: inf" << "f" << std::endl;
		std::cout << "double: inf" << std::endl;
	}
}

// //! combine with found exception?
// std::string ScalarConverter::makeString(const std::string& literal) {
// 	if (literal == "nan" || literal == "nanf")
// 		return ("nan");
// 	if (literal == "inf")
// 		return ("inf");
// 	else
// 		return ("");
// };