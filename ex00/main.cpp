#include "ScalarConverter.hpp"

int main(void)
{
    for (const std::string& test : {"123", "-99", "100.100f", "3.", "a", "A", "nan", "+inf", "-inf", "2147483648", "2147483647999.0"}) 
    {
        std::cout << "testing: " << test << std::endl;
        ScalarConverter::convert(test);
        std::cout << "\n";
    };
}


// int main(int argc, char** argv)
// {
    // if (argc == 2)
    // {
    //     try {
    //         ScalarConverter::convert(argv[1]);
    //     }
    //     catch (std::exception& e) {
    //         std::cout << "Error. " << e.what() << std::endl;
    //     }
    // }
    // else
    //     std::cout << "Error. Wrong argument count. Only 1 parameter accepted" << std::endl;
// }