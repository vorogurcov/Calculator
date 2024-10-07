#pragma once

#ifndef BASIC_FUNCTIONS
#define BASIC_FUNCTIONS

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>

namespace BasicCalcFunctions
{
	std::queue<std::string>& parseInput(std::string const& input);
	std::queue<std::string>& Shunting_Yard(std::queue<std::string> & tokens);
	static double evaluate(std::queue<std::string> & tokensRPN);
	double calculate(std::string const& input);
}


#endif // !BASIC_FUNCTIONS
