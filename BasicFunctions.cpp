#include "BasicFunctions.h"


namespace BasicCalcFunctions
{
	enum BasicSymbs {
		addition = '+', subtraction = '-', multiplication = '*', division = '/',
		leftparentheses = '(', rightparentheses = ')'
	};

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

	int getPrecedence(std::string const& token)
	{
		if (token == std::string(1, addition) || token == std::string(1, subtraction))
			return 1;
		else if (token == std::string(1, multiplication) || token == std::string(1, division))
			return 2;
	}

	std::queue<std::string>& Shunting_Yard(std::queue<std::string>& tokens)
	{
		std::queue<std::string>& tokensRNP = *new std::queue<std::string>;
		std::stack<std::string> operations;

		while (!tokens.empty())
		{

			std::string token = tokens.front();
			tokens.pop();
			if (isdigit(token[0]))
				tokensRNP.push(token);
			else if (token == std::string(1, addition) || token == std::string(1, subtraction) ||
				token == std::string(1, multiplication) || token == std::string(1, division))

			{
				if (operations.empty())
					operations.push(token);
				else
				{
					while (!operations.empty() && getPrecedence(token) < getPrecedence(operations.top()))
					{
						tokensRNP.push(operations.top());
						operations.pop();
					}
					operations.push(token);
				}
			}
			else if (token == std::string(1, leftparentheses))
				operations.push(token);
			else
			{
				while (operations.top() != std::string(1,leftparentheses))
				{
					tokensRNP.push(operations.top());
					operations.pop();
				}
				operations.pop();
			}
		}

		while (!operations.empty())
		{
			tokensRNP.push(operations.top());
			operations.pop();
		}

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