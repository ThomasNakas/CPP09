/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:08:10 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/21 18:04:09 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include  <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
	std::map<std::string, double> _exchangeRates;
	//private methods
	bool isValidDate(const std::string &date);
	bool isNotLargeValue(const std::string &value);
	bool isPositiveValue(const std::string &value);
	std::string findClosestDate(const std::string &date);
	
	public:
		BitcoinExchange();
		BitcoinExchange(const  BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void loadDatabase(const std::string &filename);
		void processInputFile(const std::string &filename);
};