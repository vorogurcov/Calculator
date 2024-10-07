#include "BasicFunctions.h"


namespace BasicCalcFunctions
{
	enum BasicSymbs {addition = '+', subtraction = '-', multiplication = '*', division = '/', 
		leftparentheses = '(', rightparentheses = ')' };
	std::queue<std::string>& parseInput(std::string const& input)
	{
		std::queue<std::string>& tokens = *new std::queue<std::string>;
		
		std::istringstream sstr(input);
		char sym;
		bool isnumber = false;
		std::string curtoken;
		while ((sym = sstr.get()) != '\n')
		{
			curtoken = "";
			
			while (isdigit(sym))
			{
				isnumber = true;
				curtoken += sym;
				sym = sstr.get();
			}

			if (isnumber == true)
			{
				tokens.push(curtoken);
				curtoken = "";
				isnumber = false;
			}

			if (sym == '\n')
				break;
			else
				tokens.push(curtoken = sym);
		};
		return tokens;
	}
	std::queue<std::string>& Shunting_Yard(std::queue<std::string> const& tokens)
	{
		std::queue<std::string> tokensRNP;
		std::stack<std::string> operations;
		return tokensRNP;
	}

	double evaluate(std::queue<std::string> const& tokensRPN)
	{
		return 2;
	}

	double calculate(std::string const& input)
	{
		std::queue<std::string> tokens = parseInput(input);
		std::queue<std::string> tokensRPN = Shunting_Yard(tokens);
		double ans = evaluate(tokensRPN);
		return ans;
	}
}