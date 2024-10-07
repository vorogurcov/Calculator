#include "BasicFunctions.h"


namespace BasicCalcFunctions
{
	enum BasicSymbs {
		addition = '+', subtraction = '-', multiplication = '*', division = '/',
		leftparentheses = '(', rightparentheses = ')'
	};

	std::queue<std::string>& parseInput(const std::string& input) {
		std::queue<std::string>& tokens = *new std::queue<std::string>;

		std::istringstream sstr(input);
		char sym;
		bool isnumber = false;
		std::string curtoken;
		bool expectUnaryMinus = true;  

		while (sstr.get(sym)) {
			curtoken = "";

			
			if (isspace(sym)) {
				continue;
			}

			
			if (isdigit(sym) || (sym == '-' && expectUnaryMinus)) {
				
				if (sym == '-') {
					curtoken += sym;  
					sstr.get(sym);     
				}

				
				while (isdigit(sym)) {
					curtoken += sym;
					if (!sstr.get(sym)) break;  
				}

				tokens.push(curtoken);
				curtoken = "";
				isnumber = true;
				expectUnaryMinus = false; 

				
				if (!isdigit(sym)) {
					sstr.unget();
				}
			}
			else {
			
				curtoken += sym;
				tokens.push(curtoken);
				isnumber = false;
				expectUnaryMinus = (sym == '(' || sym == ')' || sym == '+' || sym == '*' || sym == '/');  // Unary minus can occur after these
			}
		}

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
		std::queue<std::string>& tokensRPN = *new std::queue<std::string>;
		std::stack<std::string> operations;

		while (!tokens.empty())
		{

			std::string token = tokens.front();
			tokens.pop();
			if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])))
				tokensRPN.push(token);
			else if (token == std::string(1, addition) || token == std::string(1, subtraction) ||
				token == std::string(1, multiplication) || token == std::string(1, division))

			{
				if (operations.empty())
					operations.push(token);
				else
				{
					while (!operations.empty() && getPrecedence(token) < getPrecedence(operations.top()))
					{
						tokensRPN.push(operations.top());
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
					tokensRPN.push(operations.top());
					operations.pop();
				}
				operations.pop();
			}
		}

		while (!operations.empty())
		{
			tokensRPN.push(operations.top());
			operations.pop();
		}

		return tokensRPN;
	}

	std::string& evaluateOperation(std::string& token, std::string& arg1, std::string& arg2)
	{
		std::string& ans = *new std::string;
		if (token == std::string(1, addition))
			ans = std::to_string(std::stod(arg1) + std::stod(arg2));
		else if (token == std::string(1, subtraction))
			ans = std::to_string(std::stod(arg2) - std::stod(arg1));
		else if (token == std::string(1, multiplication))
			ans = std::to_string(std::stod(arg1) * std::stod(arg2));
		else if (token == std::string(1, division))
			ans = std::to_string(std::stod(arg2) / std::stod(arg1));
		
		return ans;
	}

	double evaluate(std::queue<std::string>& tokensRPN)
	{
		std::stack<std::string> st;

		while (!tokensRPN.empty())
		{
			std::string token = tokensRPN.front();
			tokensRPN.pop();
			if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])))
				st.push(token);
			else
			{
				std::string arg1 = st.top();
				st.pop();
				std::string arg2 = st.top();
				st.pop();
				std::string ans = evaluateOperation(token, arg1, arg2);
				st.push(ans);
			}
		}
		double ans = std::stod(st.top());
		st.pop();
		return ans;
	}

	double calculate(std::string const& input)
	{
		std::queue<std::string> tokens = parseInput(input);
		std::queue<std::string> tokensRPN = Shunting_Yard(tokens);
		double ans = evaluate(tokensRPN);
		return ans;
	}
}

namespace InterfaceFunctions
{
	std::string EquationGetter()
	{
		std::string equation;
		std::cout << "Please, type in your equation\n";
		std::getline(std::cin, equation);

		return equation;
	}

	void AnswerGetter(std::string& equation)
	{
		double ans = BasicCalcFunctions::calculate(equation);
		std::cout << equation + " = " << ans;
		
	};
}