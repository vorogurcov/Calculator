#include "BasicFunctions.h"

using std::queue;
using std::string;

int main()
{
 
	string s = "4 + 18/(9-3)";
	
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	s += '\n';

	
	int ans = BasicCalcFunctions::calculate(s);
	
	std::cout << ans;

}
