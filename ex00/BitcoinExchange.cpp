/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:08:07 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/21 17:25:05 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	this->_exchangeRates = other._exchangeRates;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if(this !=&other)
		this->_exchangeRates = other._exchangeRates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {};

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "Error: coould not open database file.\n";
		exit(1);
	}
	std::string line;
	std::getline(file, line);
	
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date, priceStr;
		if (std::getline(ss,  date, ',') && std::getline(ss, priceStr))
		{
			double price = std::stod(priceStr);
			_exchangeRates[date] = price;
		}
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if(date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	char d1, d2;
	std::stringstream ss(date);
	ss >> year >> d1 >> month >> d2 >> day;
	if (ss.fail() || d1 != '-' || d2 != '-')
		return false;
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	return true;
}

bool BitcoinExchange::isValidValue(const std::string &value)
{
	try
	{
		double val = std::stod(value);
		return val >= 0 && val <= 1000;
	}
	catch(...)
	{
		return false;
	}
	
}
std::string BitcoinExchange::findClosestDate(const std::string &date)
{
	auto it = _exchangeRates.lower_bound(date);
	if (it ==  _exchangeRates.end() || it->first > date)
	{
		if (it ==_exchangeRates.begin())
			return "";
		--it;
	}
	return it->first;
}

void BitcoinExchange::processInputFile(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "Error: could not open file.\n";
		return;
	}
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date, valueStr;
		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
		{
			std::cerr << "Error: bad input => " << date << "\n";
			continue;
		}
		double value = std::stod(valueStr); 
		std::string closestDate = findClosestDate(date);

		if (closestDate.empty())
		{
			std::cerr << "Error: no exchange rate available for " << date << "\n";
			continue;
		}
		double rate = _exchangeRates[closestDate];
		std::cout << date << " => " << value << " = " << value * rate << "\n";
	}
	file.close();
}