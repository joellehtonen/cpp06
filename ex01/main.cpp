#include "Serializer.hpp"

int main(void)
{
	std::cout << "\nTEST 1\n";
	{
		Data* mickey = new Data;

		mickey->name = "Mickey";
		mickey->number = 17;

		std::cout << "Data name: " << mickey->name << std::endl;
		std::cout << "Data number: " << mickey->number << std::endl;
		std::cout << "Pointer: " << mickey << std::endl;
		std::cout << "Pointer address: " << &mickey << std::endl;

		uintptr_t temp = Serializer::serialize(mickey);
		std::cout << "Temp: " << temp << std::endl;
		std::cout << "Temp address: " << &temp << std::endl;
		Data* converted = Serializer::deserialize(temp);

		std::cout << "Converted name: " << converted->name << std::endl;
		std::cout << "Converted number: " << converted->number << std::endl;
		std::cout << "Converted pointer: " << converted << std::endl;
		std::cout << "Converted pointer address: " << &converted << std::endl;
	
		delete mickey;
	}

	std::cout << "\nTEST 2\n";
	{
		Data* donald = nullptr;
		std::cout << "Pointer: " << donald << std::endl;
		std::cout << "Pointer address: " << &donald << std::endl;
		uintptr_t temp = Serializer::serialize(donald);
		std::cout << "Temp: " << temp << std::endl;
		std::cout << "Temp address: " << &temp << std::endl;
		Data* converted = Serializer::deserialize(temp);
		std::cout << "Converted pointer: " << converted << std::endl;
		std::cout << "Converted pointer address: " << &converted << std::endl;
	}
}