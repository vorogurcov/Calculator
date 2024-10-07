#include "BasicFunctions.h"

using std::queue;
using std::string;

int main()
{
 
	string s = "(5        +127)*3 +17";
	
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	s += '\n';
	queue<string> q = BasicCalcFunctions::parseInput(s);
	

	//int ans = BasicCalcFunctions::calculate(s);
	
	

}
