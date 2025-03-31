/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:08:07 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/31 16:42:04 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Btc::Btc() {}

Btc::Btc(const Btc &other)
{
	this->_exchangeRates = other._exchangeRates;
}

Btc &Btc::operator=(const Btc &other)
{
	if(this !=&other)
		this->_exchangeRates = other._exchangeRates;
	return *this;
}

Btc::~Btc() {};

void Btc::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cerr << "Error: could not open database file.\n";
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

bool Btc::isValidDate(const std::string &date)
{
	if(date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	char d1, d2;
	std::stringstream ss(date);
	ss >> year >> d1 >> month >> d2 >> day;
	if (ss.fail() || d1 != '-' || d2 != '-')
		return false;
	if (month < 1 || month > 12 || day < 1 || day > 31 
		|| (month == 2 && day > 29) 
		|| (year%4 != 0 && month == 2 && day > 28)
		|| ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
		return false;
	return true;
}

bool Btc::isPositiveValue(const std::string &value)
{
	try
	{
		double val = std::stod(value);
		return val >= 0;
	}
	catch(...)
	{
		return false;
	}
	
}

bool Btc::isNotLargeValue(const std::string &value)
{
	try
	{
		double val = std::stod(value);
		return val <= 1000;
	}
	catch(...)
	{
		return false;
	}
	
}
std::string Btc::findClosestDate(const std::string &date)
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

void Btc::processInputFile(const std::string &filename)
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
		line.erase(0, line.find_first_not_of(" \t\n\r"));
		line.erase(line.find_last_not_of(" \t\n\r") + 1);
		if (line.empty())
			continue;
		std::stringstream ss(line);
		std::string date, valueStr;
		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
		{
			std::cerr << "Error: bad input => " << date << "\n";
			continue;
		}
		date = date.substr(0, date.find_last_not_of(" ") + 1); //trim spaces
		valueStr = valueStr.substr(valueStr.find_first_not_of(" "));

		if (!isValidDate(date))
		{
			std::cerr<< "Error: bad input => " << date << "\n";
			continue; 
		}
		if (!isPositiveValue(valueStr))
		{
			std::cerr << "Error: not a positive number.\n";
			continue;
		}
		if (!isNotLargeValue(valueStr))
		{
			std::cerr << "Error: too large a number.\n";
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