/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:27 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/24 19:52:28 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cmath>

class RPN
{
	const std::string set = "0123456789+-*/";
	const std::string numbers = "0123456789";
	const std::string symbols = "+-*/";
	
	public:
		enum cases {DIVISION_BY_ZERO = -214383648,
					IS_DECIMAL = -214482648};
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);

		int		calculate(std::stack<char> chr);
		//helpers
		bool	foundIn(const std::string &set, const char ch);
		//checkers
		// only numbers and "+ - * /"
		bool	validChars(const std::string& input);
		bool	validSeqs(const std::string& input);
		int		validRPN(const std::string& input);
		std::stack<char> prepForCalc(const std::string& input);
};