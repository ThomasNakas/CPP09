#include "RPN.hpp"

int main (int argc, char* argv[])
{
	RPN t;
	int res;
	if( argc == 2)
	{
		//char validation
		if (!t.validChars(argv[1]))
		{
			std::cerr << "Error: not valid chars\n";
			return -1;
		}
		else if (!t.validSeqs(argv[1]))
		{
			std::cerr << "Error: non valid sequence\n";
			return -1;
		}
		int valid = t.validRPN(argv[1]);
		if (valid < 1)
		{
			std::cerr << "Error: invalid RPN: too many operators\n";
			return -1;
		}
		else if (valid > 1)
		{
			std::cerr << "Error: invalid RPN: too many numbers\n";
			return -1;
		}
		else
		{
			res = t.calculate(t.prepForCalc(argv[1]));
			if (res == t.DIVISION_BY_ZERO)
				std::cerr << "Error: division by 0 is not allowed\n";
			else if (res == t.IS_DECIMAL)
				std::cerr << "Error: The result has a decimal\n";
			else 
				std::cout << res << std::endl;
		}
	}
	else
		std::cerr 
		<< "Error: you need exactly one argument for the ./RPN\n"
		<< "     : ====> ./RPN <arg> <====="
		<< std::endl;	
	return 0;
}	