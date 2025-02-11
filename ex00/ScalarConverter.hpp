#pragma once
#include <string>
#include <iostream>

class ScalarConverter {
	public:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& copy);
		ScalarConverter& operator=(const ScalarConverter& copy);

		static void convert();
};