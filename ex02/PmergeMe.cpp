/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/24 19:52:48 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

};
PmergeMe::~PmergeMe()
{
};
PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
};

void PmergeMe::printRes(const std::vector<int> vec)
{
	for(int n : vec)
		std::cout << n << " ";
	std::cout << std::endl;
}

bool PmergeMe::IsNbr(const std::string& str)
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool PmergeMe::IsPInt(const std::string& str)
{
	return  (
				std::stod(str) >= 0.0 
				&& std::stod(str) <= 2147483647.0
			);
};

std::vector<int> PmergeMe::fastSort(const std::vector<int> numbers)
{
	std::vector<int> temp = numbers;
	for(size_t i = 0; i != temp.size() - 1; i++)
		for (size_t j = i + 1; j != temp.size(); j++)
			if (temp[i] > temp[j])
				std::swap(temp[i], temp[j]);
	return temp;
}

int	PmergeMe::spPow(int n1, int n2)
{
	return ((int)pow((long double)n1, (long double)n2));
};

PmergeMe::Group::Group() : level(1)
{
};
PmergeMe::Group::Group(const std::vector<int> elems) : elements(elems), representator(elems.back())
{
};

PmergeMe::Group::Group(const PmergeMe::Group& other)
{
	this->elements = other.elements;
	this->representator = other.representator;
	this->level = other.level;
}
PmergeMe::Group& PmergeMe::Group::operator=(const PmergeMe::Group& other)
{
	if (this != &other)
	{
		this->elements = other.elements;
		this->representator = other.representator;
		this->level = other.level;
	}
	return *this;
}
PmergeMe::Group::~Group(){};

std::vector<PmergeMe::Group> PmergeMe::mergeGroups(std::vector<PmergeMe::Group> groups)
{
	while (groups.size() > 3)
	{
		std::vector<Group> mergeGroups;
		for (size_t i = 0; i + 1 < groups.size(); i+=2)
		{
			std::vector<int> mergedElemets = groups[i].elements;
			mergedElemets.insert(mergedElemets.end(), groups[i + 1].elements.begin(), groups[i + 1].elements.end());
			mergeGroups.emplace_back(mergedElemets);
		}
		std::sort(mergeGroups.begin(), mergeGroups.end(), [](const Group& a, const Group& b)
	{
		return a.representator < b.representator;
	});
	groups = mergeGroups;
	for (Group gr : groups)
		gr.level *= 2; 
	}
	return groups;
}