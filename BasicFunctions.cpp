#include "BasicFunctions.h"


namespace BasicCalcFunctions
{
    enum BasicSymbs {
        addition = '+', subtraction = '-', multiplication = '*', division = '/',
        leftparentheses = '(', rightparentheses = ')', power = '^',
        sin_op = 's', cos_op = 'c', ln_op = 'l'
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

                while (isdigit(sym) || sym == '.') {
                    curtoken += sym;
                    if (!sstr.get(sym)) break;
                }

                tokens.push(curtoken);
                curtoken = "";
                isnumber = true;
                expectUnaryMinus = false;

                if (!isdigit(sym) && sym != '.') {
                    sstr.unget();
                }
            }
            else {
                if (sym == 's' || sym == 'c' || sym == 'l') {
                    std::string func(1, sym);
                    while (isalpha(sstr.peek())) {
                        sstr.get(sym);
                        func += sym;
                    }

                    tokens.push(func);
                    expectUnaryMinus = true;
                }
                else {
                    curtoken += sym;
                    tokens.push(curtoken);
                    isnumber = false;
                    expectUnaryMinus = (sym == '(' || sym == ')' || sym == '+' || sym == '*' || sym == '/' || sym == '^');
                }
            }
        }

        return tokens;
    }

    int getPrecedence(const std::string& token) {
        if (token == std::string(1, addition) || token == std::string(1, subtraction))
            return 1;
        else if (token == std::string(1, multiplication) || token == std::string(1, division))
            return 2;
        else if (token == "^")
            return 3;
        else if (token == "sin" || token == "cos" || token == "ln")
            return 4;
        return 0;
    }

    std::queue<std::string>& Shunting_Yard(std::queue<std::string>& tokens) {
        std::queue<std::string>& tokensRPN = *new std::queue<std::string>;
        std::stack<std::string> operations;

        while (!tokens.empty()) {
            std::string token = tokens.front();
            tokens.pop();

            if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
                tokensRPN.push(token);
            }
            else if (token == std::string(1, addition) || token == std::string(1, subtraction) ||
                token == std::string(1, multiplication) || token == std::string(1, division) || token == "^") {

                while (!operations.empty() && getPrecedence(token) <= getPrecedence(operations.top())) {
                    tokensRPN.push(operations.top());
                    operations.pop();
                }
                operations.push(token);

            }
            else if (token == std::string(1, leftparentheses)) {
                operations.push(token);
            }
            else if (token == std::string(1, rightparentheses)) {
                while (operations.top() != std::string(1, leftparentheses)) {
                    tokensRPN.push(operations.top());
                    operations.pop();
                }
                operations.pop();
            }
            else if (token == "sin" || token == "cos" || token == "ln") {
                operations.push(token);
            }
        }

        while (!operations.empty()) {
            tokensRPN.push(operations.top());
            operations.pop();
        }

        return tokensRPN;
    }

    std::string& evaluateOperation(std::string& token, std::string& arg1, std::string& arg2) {
        std::string& ans = *new std::string;

        if (token == std::string(1, addition))
            ans = std::to_string(std::stod(arg2) + std::stod(arg1));
        else if (token == std::string(1, subtraction))
            ans = std::to_string(std::stod(arg2) - std::stod(arg1));
        else if (token == std::string(1, multiplication))
            ans = std::to_string(std::stod(arg2) * std::stod(arg1));
        else if (token == std::string(1, division))
            ans = std::to_string(std::stod(arg2) / std::stod(arg1));
        else if (token == "^")
            ans = std::to_string(std::pow(std::stod(arg2), std::stod(arg1)));

        return ans;
    }

    std::string evaluateFunction(std::string& token, std::string& arg) {
        std::string ans;

        if (token == "sin")
            ans = std::to_string(std::sin(std::stod(arg)));
        else if (token == "cos")
            ans = std::to_string(std::cos(std::stod(arg)));
        else if (token == "ln")
            ans = std::to_string(std::log(std::stod(arg)));

        return ans;
    }

    double evaluate(std::queue<std::string>& tokensRPN) {
        std::stack<std::string> st;

        while (!tokensRPN.empty()) {
            std::string token = tokensRPN.front();
            tokensRPN.pop();

            if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
                st.push(token);
            }
            else if (token == "sin" || token == "cos" || token == "ln") {
                std::string arg = st.top();
                st.pop();
                std::string ans = evaluateFunction(token, arg);
                st.push(ans);
            }
            else {
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

    double calculate(const std::string& input) {
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