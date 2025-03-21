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
	int			decimalCount = 0;

	if (literal.length() == 0)
		throw std::invalid_argument("Argument cannot be empty");

	isFloatDouble(literal, somethingFound, foundFloat, foundDouble, decimalCount);
	if (somethingFound == false)
		isInt(literal, somethingFound, foundInt);
	if (somethingFound == false)
		isChar(literal, somethingFound, foundChar);
	if (somethingFound == false)
		isException(literal, exceptionType);
	if (somethingFound == false && exceptionType == "")
		throw std::invalid_argument("Argument is not a literal");

	char	literalChar = '0';
	int		literalInt = 0;
	float	literalFloat = 0.0f;
	double	literalDouble = 0.0; 

	if (foundChar == true)
	{
		literalChar = makeChar(literal, exceptionType);
		convertFromChar(literalChar, literalInt, literalFloat, literalDouble);
	}
	else if (foundInt == true)
	{
		literalInt = makeInt(literal, exceptionType);
		convertFromInt(literalChar, literalInt, literalFloat, literalDouble);
	}
	else if (foundFloat == true)
	{
		literalFloat = makeFloat(literal, exceptionType);
		convertFromFloat(literalChar, literalInt, literalFloat, literalDouble);
	}
	else if (foundDouble == true)
	{
		literalDouble = makeDouble(literal, exceptionType);
		convertFromDouble(literalChar, literalInt, literalFloat, literalDouble);
	}
	
	if (exceptionType != "")
		handleExceptions(exceptionType, literalInt, literalFloat, literalDouble);

	printLiterals(literalChar, literalInt, literalFloat, literalDouble, exceptionType, decimalCount, foundInt);
};

void ScalarConverter::isFloatDouble(const std::string& literal, bool& somethingFound, bool& foundFloat, bool& foundDouble, int& decimalCount) { 

	size_t	periodPosition	= literal.find('.');
	size_t	lastPosition 	= literal.length() - 1;

	if (lastPosition > 310)
		throw std::invalid_argument("String is too long");

	if (periodPosition == std::string::npos)
		return ;
	for (int i = periodPosition - 1; i >= 0; i--)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
		{
			if (i == 0 && (literal[0] == '+' || literal[0] == '-'))
				break ;
			else
				return ;
		}
	}
	for (size_t i = periodPosition + 1; i < lastPosition; i++)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
		decimalCount += 1;
	}
	if (literal[lastPosition] != 'f')
	{
		if (std::isdigit(static_cast<unsigned char>(literal[lastPosition])) != false || literal[lastPosition] == '.')
		{
			somethingFound = true;
			foundDouble = true;
			decimalCount += 1;
		}
		return ;
	}
	somethingFound = true;
	foundFloat = true;
	return ;
};

void ScalarConverter::isInt(const std::string& literal, bool& somethingFound, bool& foundInt)
{
	size_t len = literal.length() - 1;
	for (size_t i = 0; i <= len; i++)
	{
		if (i == 0 && (literal[0] == '+' || literal[0] == '-'))
			i++;
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
	}
	somethingFound = true;
	foundInt = true;
	return ;
}

void ScalarConverter::isChar(const std::string& literal, bool& somethingFound, bool& foundChar)
{
	size_t len = literal.length();
	if (len != 1)
		return ;
	if (std::isprint(static_cast<unsigned char>(literal[0])) == false)
		return ;
	somethingFound = true;
	foundChar = true;
	return ;
};

void ScalarConverter::isException(const std::string& literal, std::string& exceptionType)
{
	if (literal == "nan" || literal == "nanf")
		exceptionType = "nan";
	else if (literal == "+inf" || literal == "+inff" || literal == "inf")
		exceptionType = "+inf";
	else if (literal == "-inf" || literal == "-inff")
		exceptionType = "-inf";
	return ;
};

double ScalarConverter::makeDouble(const std::string& literal, std::string& exceptionType) {
	double check = std::stod(literal);
	checkLimits(check, exceptionType);
	return check;
};

float ScalarConverter::makeFloat(const std::string& literal, std::string& exceptionType) {
	double check = std::stod(literal);
	checkLimits(check, exceptionType);
	return static_cast<float>(check);
};

int ScalarConverter::makeInt(const std::string& literal, std::string& exceptionType) {
	double check = std::stod(literal);
	checkLimits(check, exceptionType);
	return static_cast<int>(check);
};

char ScalarConverter::makeChar(const std::string& literal, std::string& exceptionType) {
	if (std::isprint(static_cast<unsigned char>(literal[0])) == false)
	{
		exceptionType = "non-printable";
		return (static_cast<char>(0));
	}
	return static_cast<char>(literal[0]);
};

void ScalarConverter::checkLimits(const double& check, std::string& exceptionType)
{
	if (check < 32 || check	> 126)
	{
		exceptionType = "non-printable";
		if (check < 0 || check > 127)
			exceptionType += " | impossible conversion";
		if (check < INT_MIN || check > INT_MAX)
			exceptionType += " | int overflow";
	}
	return ;
}

void ScalarConverter::convertFromChar(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble) {
	literalInt = static_cast<int>(literalChar);
	literalFloat= static_cast<float>(literalChar);
	literalDouble = static_cast<double>(literalChar);
};

void ScalarConverter::convertFromInt(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble)  {
	literalChar = static_cast<char>(literalInt);
	literalFloat= static_cast<float>(literalInt);
	literalDouble = static_cast<double>(literalInt);
};

void ScalarConverter::convertFromFloat(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble)  {
	literalChar = static_cast<char>(literalFloat);
	literalInt = static_cast<int>(literalFloat);
	literalDouble = static_cast<double>(literalFloat);
};

void ScalarConverter::convertFromDouble(char& literalChar, int& literalInt, float& literalFloat, double& literalDouble)  {
	literalChar = static_cast<char>(literalDouble);
	literalInt = static_cast<int>(literalDouble);
	literalFloat = static_cast<float>(literalDouble);
};

void ScalarConverter::handleExceptions(const std::string& exceptionType, int& literalInt, float& literalFloat, double& literalDouble) {
	if (exceptionType == "nan")
	{
		literalFloat = std::stof("nan");
		literalDouble = std::stof("nan");
		return ;
	}
	else if (exceptionType == "+inf" || exceptionType == "inf")
	{
		literalInt = 2147483647;
		literalFloat = std::stof("inf");
		literalDouble = std::stod("inf");
	}
	else if (exceptionType == "-inf")
	{
		literalInt = -2147483648;
		literalFloat = std::stof("-inf");
		literalDouble = std::stod("-inf");
	}
	return ;
};

void ScalarConverter::printLiterals(const char& literalChar, const int& literalInt, const float& literalFloat, const double& literalDouble, \
	const std::string& exceptionType, int& decimalCount, bool& foundInt) {
	if (decimalCount == 0)
		decimalCount = 1;

	//char
	if (exceptionType.find("impossible conversion") != std::string::npos)
		std::cout << "char: impossible" << std::endl;
	else if (exceptionType.find("non-printable") != std::string::npos)
		std::cout << "char: non-printable" << std::endl;
	else if (exceptionType == "")
		std::cout << "char: " << literalChar << std::endl;
	else
		std::cout << "char: impossible" << std::endl;

	//int
	if (exceptionType.find("int overflow") != std::string::npos || exceptionType == "nan")
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << literalInt << std::endl;

	//float
	if (exceptionType.find("int overflow") != std::string::npos && foundInt == true)
		std::cout << "float: impossible" << std::endl;
	else
	{
		std::cout << std::fixed << std::setprecision(decimalCount);
		std::cout << "float: " << literalFloat << "f" << std::endl;
	}

	//double
	if (exceptionType.find("int overflow") != std::string::npos && foundInt == true)
		std::cout << "double: impossible" << std::endl;
	else
	{
		std::cout << std::fixed << std::setprecision(decimalCount);
		std::cout << "double: " << literalDouble << std::endl;
	}
}