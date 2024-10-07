#include "BasicFunctions.h"

using std::queue;
using std::string;

int main()
{
 
	string equation = InterfaceFunctions::EquationGetter();
	InterfaceFunctions::AnswerGetter(equation);

}
