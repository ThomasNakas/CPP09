#pragma once

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class RPN
{
	const std::string set = "0123456789+-*/";
	const std::string numbers = "0123456789";
	const std::string symbols = "+-*/";

	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);

		int		calculate(const std::string& input);
		//helpers
		bool	foundIn(const std::string &set, const char ch);
		//checkers
		// only numbers and "+ - * /"
		bool	validChars(const std::string& input);
		bool	validSeqs(const std::string& input);
		int		validRPN(const std::string& input);
		std::stack<char> prepForCalc(const std::string& input);
};