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

bool 		ScalarConverter::foundDouble = false;
bool 		ScalarConverter::foundFloat = false;
bool 		ScalarConverter::foundInt = false;
bool 		ScalarConverter::foundChar = false;
std::string ScalarConverter::exceptionType = "";

void ScalarConverter::convert(std::string literal) {
	if (literal.length() == 0)
		throw std::invalid_argument("Argument cannot be empty");

	isFloatDouble(literal);
	if (nothingFound() == true)
		isInt(literal);
	if (nothingFound() == true)
		isChar(literal);
	if (nothingFound() == true)
		isException(literal);
	if (nothingFound() == true)
		throw std::invalid_argument("Argument is not a literal");

	std::cout << "boolchar = " << foundChar << std::endl;
	std::cout << "boolint = " << foundInt << std::endl;
	std::cout << "boolfloat = " << foundFloat << std::endl;
	std::cout << "booldouble = " << foundDouble << std::endl;
	std::cout << "boolexception = " << exceptionType << std::endl;

	if (foundChar == true)
		handleChar(literal);
	else if (foundInt == true)
		handleInt(literal);
	else if (foundFloat == true)
		handleFloat(literal);
	else if (foundDouble == true)
		handleDouble(literal);
	else if (exceptionType != "")
		handleException();

	//TODO handle nan, nanf, -inff, +inff
	//TODO handle conversions that dont make sense, overflows
	//TODO print messages for these ("impossible"?)
	//? which headers handle numeric limits and special values
};

bool ScalarConverter::nothingFound()
{	
	if (foundDouble == false && foundFloat == false && foundInt == false && foundChar == false && exceptionType == "")
		return true;
	else
		return false;
};

// checks if the literal type is float or double
//! test with 1.f and 1.
void ScalarConverter::isFloatDouble(const std::string& literal) { 

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
			foundDouble = true;
		return ;
	}

	foundFloat = true;
	return ;
};

// checks if the literal type is int
//? check for signs?
void ScalarConverter::isInt(const std::string& literal)
{
	size_t len = literal.length() - 1;
	for (size_t i = 0; i <= len; i++)
	{
		if (std::isdigit(static_cast<unsigned char>(literal[i])) == false)
			return ;
	}
	foundInt = true;
	return ;
}

// checks if the literal type is char
void ScalarConverter::isChar(const std::string& literal)
{
	size_t len = literal.length();
	if (len != 1)
		return ;
	if (std::isprint(static_cast<unsigned char>(literal[0])) == false)
		return ;
	foundChar = true;
	return ;
};

//! get rid of if/else?
void ScalarConverter::isException(const std::string& literal)
{
	if (literal == "nan" || literal == "nanf")
		exceptionType = "nan";
	else if (literal == "+inf" || literal == "-inf" || literal == "+inff" || literal == "-inff")
		exceptionType = "inf";
	return ;
};

void ScalarConverter::printNumbers(const std::string& literal) {
	double	printDouble = makeDouble(literal);
	float	printFloat = makeFloat(literal);
	int		printInt = makeInt(literal);
	char	printChar = makeChar(literal);

	std::cout << "char: " << printChar << std::endl;
	std::cout << "int: " << printInt << std::endl;
	std::cout << "float: " << printFloat << "f" << std::endl;
	std::cout << "double: " << printDouble << std::endl;
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

// add exception if char is not printable
char ScalarConverter::makeChar(const std::string& literal) {
	unsigned int	asInteger = stoi(literal);
	return static_cast<char>(asInteger);
};

//! combine with found exception?
std::string ScalarConverter::makeString(const std::string& literal) {
	if (literal == "nan" || literal == "nanf")
		return ("nan");
	if (literal == "inf")
		return ("inf");
	else
		return ("");
};