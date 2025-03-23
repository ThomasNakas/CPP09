#include "RPN.hpp"

	RPN::RPN()
	{

	};

	RPN::~RPN()
	{

	};

	RPN::RPN(const RPN& other)
	{
		*this = other;
	};

	RPN& RPN::operator=(const RPN& other)
	{
		(void)other;
		return *this;
	};

	bool RPN::foundIn(const std::string &set, const char ch)
	{
		return ((set.find(ch) != std::string::npos) 
				? true : false);
	};
	bool RPN::validChars(const std::string& input)
	{
		for (char ch : input)
			if (!foundIn(set, ch) && !isspace(ch))
				return false;
		return true;
	}
	bool RPN::validSeqs(const std::string& input)
	{
		for (unsigned long i = 0; i != input.length(); i++)
			if (foundIn(numbers, input[i]) 
				&& input[i + 1]
				&& foundIn(numbers, input[i + 1]))
				return false;
		return true;
	}

	int RPN::validRPN(const std::string& input)
	{
		int sum = 0;
		if (input.empty())
			return sum;
		foundIn(numbers, input[0]) ? sum++ :
		foundIn(symbols, input[0]) ? sum-- : 
		NULL;
		unsigned int begin = 0;
		for (; begin != input.length(); begin++)
			if (!isspace(input[begin]))
				break ;
		for (char ch : input.substr(begin, input.length()))
		{
			foundIn(numbers, ch) ? sum++ :
			foundIn(symbols, ch) ? sum-- : 
			NULL;
			if (sum < 1)
				return sum;
		}
		return sum;
	}

	std::stack<char> RPN::prepForCalc(const std::string& input)
	{
		std::stack<char> st;
		for (char ch : input)
			if(foundIn(set,ch))
					st.push(ch);
		std::stack<char> res;
		while(!st.empty())
		{
			res.push(st.top());
			st.pop();
		}
		return res;
	};
