#include "BasicFunctions.h"
#include "CommandManagerHeader.h"

using std::queue;
using std::string;

int main()
{
	CommandManager::LoadPlugins();
	string equation = InterfaceFunctions::EquationGetter();
	InterfaceFunctions::AnswerGetter(equation);

}
