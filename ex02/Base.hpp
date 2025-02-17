#pragma once
#include <string>
#include <iostream>
#include <random>
#include <exception>

class Base {
	public:
		virtual ~Base();
};

Base*	generate(void);
void	identify(Base* p);
void	identify(Base& p);