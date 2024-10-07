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
	static std::queue<std::string>& parseInput(std::string const& input);
	static std::queue<std::string>& Shunting_Yard(std::queue<std::string> & tokens);
	static double evaluate(std::queue<std::string> & tokensRPN);
	static std::string& evaluateOperation(std::string& token, std::string& arg1, std::string& arg2);
	double calculate(std::string const& input);
}

namespace InterfaceFunctions
{
	std::string EquationGetter();
	void AnswerGetter(std::string& equation);
}
#endif // !BASIC_FUNCTIONS
