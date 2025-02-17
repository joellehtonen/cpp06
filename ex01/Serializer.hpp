#pragma once
#include <string>
#include <iostream>
#include <cstdint>

struct Data
{
	std::string		name;
	unsigned int	number;
};

class Serializer {
	private:
		Serializer();
		~Serializer();
		Serializer(const Serializer& copy);
		Serializer& operator=(const Serializer& copy);
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};