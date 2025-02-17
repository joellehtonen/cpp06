#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base() {};

Base* generate() {
	std::random_device	device;
	unsigned int 		seed = device();
	//std::cout << "Device seed: " << seed << std::endl;

	std::srand(seed);
	int index = rand() % 3;
	switch (index)
	{
		case 0:
		{
			std::cout << "created A\n";
			return (new A());
		}
		case 1:
		{
			std::cout << "created B\n";
			return (new B());
		}
		case 2:
		{
			std::cout << "created C\n";
			return (new C());
		}
	}
	return nullptr;
};

void identify(Base* p) {
	A* isA = dynamic_cast<A*>(p);
	if (isA != nullptr)
	{
		std::cout << "pointer is of class A\n";
		return ; 
	}
	B* isB = dynamic_cast<B*>(p);
	if (isB != nullptr)
	{
		std::cout << "pointer is of class B\n";
		return ; 
	}
	C* isC = dynamic_cast<C*>(p);
	if (isC != nullptr)
	{
		std::cout << "pointer is of class C\n";
		return ; 
	}
};

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "reference is of class A\n";
		return ;
	} catch (std::exception& e) { }
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "reference is of class B\n";
		return ;
	} catch (std::exception& e) { }
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "reference is of class C\n";
		return ;
	} catch (std::exception& e) { }
};
