#include "Base.hpp"

int main(void)
{
	std::cout << "\nTEST #1 (with pointers)\n";
	{
		Base* test1 = generate();
		Base* test2 = generate();
		Base* test3 = generate();
		identify(test1);
		identify(test2);
		identify(test3);
		delete (test1);
		delete (test2);
		delete (test3);
	}

	std::cout << "\nTEST #2 (with references)\n";
	{
		Base* test1 = generate();
		Base* test2 = generate();
		Base* test3 = generate();
		try {
			identify(*test1);
			identify(*test2);
			identify(*test3);
		}
		catch (std::exception& e) {
			std::cout << "Error. " << e.what() << std::endl;
		}
		delete (test1);
		delete (test2);
		delete (test3);
	}
}