#include "RPN.hpp"

int main (int argc, char* argv[])
{
	RPN t;
	if( argc == 2)
	{
		//char validation
		if (t.validChars(argv[1]))
			std::cout << "valid chars \n";
		else
			std::cerr << "not valid chars\n";
		//sequence validation
		std::cout << "\\\\==================\n";
		if (t.validSeqs(argv[1]))
			std::cout << "valid sequence \n";
		else
			std::cerr << "non valid sequence \n";
		std::cout << "\\\\==================\n";
		int valid = t.validRPN(argv[1]);
		if (valid < 1)
			std::cerr << "invalid RPN: too many operators \n";
		else if (valid == 1)
			std::cout << "valid RPN\n";
		else
			std::cerr << "invalid RPN: too many numbers \n";
	}
	return 0;
}	