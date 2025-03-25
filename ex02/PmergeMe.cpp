/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/25 13:51:49 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
//========PmergeMe Default Functions=========
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
//========Group Default Functions=============
PmergeMe::Group::Group()
{
};
PmergeMe::Group::Group(std::vector<int> elems) : elements(elems), representator(elems.back())
{
};

PmergeMe::Group::Group(const PmergeMe::Group& other)
{
	this->elements = other.elements;
	this->representator = other.representator;
}
PmergeMe::Group& PmergeMe::Group::operator=(const PmergeMe::Group& other)
{
	if (this != &other)
	{
		this->elements = other.elements;
		this->representator = other.representator;
	}
	return *this;
}
PmergeMe::Group::~Group(){};
//========Helper Functions====================
void PmergeMe::printRes(const std::vector<int> vec)
{
	for(int n : vec)
		std::cout << n << " ";
	std::cout << std::endl;
}

void PmergeMe::printRes(const std::vector<PmergeMe::Group> groups)
{
	for (Group gr : groups)
	{
		std::cout << "[";
		for (int n : gr.elements)
			if (n != gr.elements[gr.elements.size()])
				std::cout << n << " ";
		std::cout << "]";
	}
	std::cout << std::endl;
}

//========Checker functions=====================
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

std::vector<PmergeMe::Group> PmergeMe::mergeGroups(std::vector<PmergeMe::Group> groups)
{
	while (groups.size() > 3)
	{
		std::vector<Group> mergeGroups;
		for (const PmergeMe::Group& gr : groups)
		{
			std::cout << "[";
			for (int nbr : gr.elements)
				std::cout << nbr << " ";
			std::cout << "]";
		}
		std::cout << std::endl;
		for (size_t i = 0; i + 1 < groups.size(); i+=2)
		{
			std::vector<int> mergedElemets = groups[i].elements;
			mergedElemets.insert(mergedElemets.end(),
			groups[i + 1].elements.begin(), 
			groups[i + 1].elements.end());
			mergeGroups.emplace_back(mergedElemets);
		}
		if (groups.size() % 2 != 0)
			mergeGroups.emplace_back(groups[groups.size() - 1].elements);
		for (size_t i = 0; i + 1 < mergeGroups.size(); i+=2)
			if (mergeGroups[i].representator > mergeGroups[i + 1].representator)
				std::swap(mergeGroups[i], mergeGroups[i + 1]);
	groups = mergeGroups;
	for (const PmergeMe::Group& gr : groups)
		{
			std::cout << "[";
			for (int nbr : gr.elements)
				std::cout << nbr << " ";
			std::cout << "]";
		}
		std::cout << std::endl;
	l++;
	std::cout << "Level: "<< l << std::endl;
	std::cout << "the size: " <<mergeGroups.size() << std::endl;
	}
	
	return groups;
}
//Helper functions outside of class
int	spPow(int n1, int n2)
{
	return ((int)pow((long double)n1, (long double)n2));
};
int jSeq(int n)
{
	return ((spPow(2, n) - spPow(-1, n))/3);
}

void BFindAndUpdateVec(std::vector<int>& vec, 
	int start, int end, int element)
{
	while ((end-start) + 1 > 2)
	{
		std::cout << "start, end :" << start << ", " << end << std::endl;
		if (element > vec[(end - start) / 2 + start])
			start = (end - start) / 2 + 1 + start;
		else
			end = (end - start) / 2 - 1 + start;
		for (int i = start; i <= end; i++)
			std::cout << i << " ";
		std::cout << std::endl;
		// BFindPos(vec, start, end, element);
	}
	// for (int i = start; i <= end; i++)
	// 		std::cout << i << " ";
	// std::cout << std::endl;
	if (element >= vec[end])
	{
		if ((size_t)end == vec.size() -1)
		{
			vec.push_back(element);
			return ;
		}
		vec.insert(vec.begin() + end + 1, element);
	}
	else if (element < vec[end] && element >= vec[start])
		vec.insert(vec.begin() + end, element);
	else
		vec.insert(vec.begin(), element);
}

// void BUpdateVec(std::vector<int>& vec, int element, int position)
// {
	
// }