/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:19 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/24 19:52:20 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
		{
			if ((foundIn(numbers, input[i]) 
					&& input[i + 1]
					&& foundIn(numbers, input[i + 1])) 
				||
				((input[i] == '-' || input[i] == '+')
					&& foundIn(numbers, input[i + 1]))	
			)
				return false;
		}
		return true;
	}

	int RPN::validRPN(const std::string& input)
	{
		int sum = 0;
		if (input.empty())
			return sum;
		unsigned int begin = 0;
		for (; begin != input.length(); begin++)
			if (!isspace(input[begin]))
				break ;
		foundIn(numbers, input[begin]) ? sum++ :
		foundIn(symbols, input[begin]) ? sum-- : 
		NULL;
		for (char ch : input.substr(begin + 1, input.length()))
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

	int		RPN::calculate(std::stack<char> chr)
	{
		double res = 0.0;

		std::stack<double> dbl;

		while(!chr.empty())
		{
			double first;
			double second;

			char current = chr.top();
			if (foundIn(numbers, current))
			{
				dbl.push((double)(current - '0'));
				chr.pop();
				continue ;
			}
			second = dbl.top();
			dbl.pop();
			first  =dbl.top();
			dbl.pop();
			if (current == '+')
				res = first + second;
			else if (current == '-')
				res = first - second;
			else if (current == '*')
				res = first * second;
			else 
			{
				if (second == 0.0)
					return DIVISION_BY_ZERO;
				res = first / second;
			}
			dbl.push(res);
			chr.pop();
		}
		return ((res == std::floor(res)) ? (int)(res) : IS_DECIMAL);
	};
