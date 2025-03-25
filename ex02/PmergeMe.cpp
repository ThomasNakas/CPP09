/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/25 17:25:37 by tnakas           ###   ########.fr       */
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
PmergeMe::Group::Group(std::vector<int> lms) : lms(lms), repr(lms.back())
{
};

PmergeMe::Group::Group(const PmergeMe::Group& other)
{
	this->lms = other.lms;
	this->repr = other.repr;
}
PmergeMe::Group& PmergeMe::Group::operator=(const PmergeMe::Group& other)
{
	if (this != &other)
	{
		this->lms = other.lms;
		this->repr = other.repr;
	}
	return *this;
}
PmergeMe::Group::~Group(){};

//========Helper Functions====================
void PmergeMe::printRes(const std::vector<int> vec)
{
	for(int n : vec)
	{
		std::cout << n; 
		if (n != vec[vec.size() -1])
			std::cout << " ";
	}
}

void PmergeMe::printRes(const std::vector<PmergeMe::Group> groups)
{
	for (Group gr : groups)
	{
		std::cout << "[";
		printRes(gr.lms);
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

//========Logic Fucntions=======================
std::vector<PmergeMe::Group> PmergeMe::pairMergeSorting(std::vector<PmergeMe::Group> groups)
{
	while (groups.size() > 3)
	{
		std::vector<Group> pairMergeSorting;
		// for (const PmergeMe::Group& gr : groups)
		// {
		// 	std::cout << "[";
		// 	for (int nbr : gr.lms)
		// 		std::cout << nbr << " ";
		// 	std::cout << "]";
		// }
		// std::cout << std::endl;
		for (size_t i = 0; i + 1 < groups.size(); i+=2)
		{
			std::vector<int> mergedElemets = groups[i].lms;
			mergedElemets.insert(mergedElemets.end(),
			groups[i + 1].lms.begin(), 
			groups[i + 1].lms.end());
			pairMergeSorting.emplace_back(mergedElemets);
		}
		if (groups.size() % 2 != 0)
			pairMergeSorting.emplace_back(groups[groups.size() - 1].lms);
		for (size_t i = 0; i + 1 < pairMergeSorting.size(); i+=2)
			if (pairMergeSorting[i].repr > pairMergeSorting[i + 1].repr)
				std::swap(pairMergeSorting[i], pairMergeSorting[i + 1]);
	groups = pairMergeSorting;
	for (const PmergeMe::Group& gr : groups)
		{
			std::cout << "[";
			for (int nbr : gr.lms)
				std::cout << nbr << " ";
			std::cout << "]";
		}
		std::cout << std::endl;
	l++;
	std::cout << "Level: "<< l << std::endl;
	std::cout << "the size: " << pairMergeSorting.size() << std::endl;
	}
	
	return groups;
}

void PmergeMe::BinarySortOne(std::vector<Group>& vec, 
	int start, int end, Group element)
{
	while((end - start) + 1 > 2)
	{
		if (element.repr > vec[(end - start) / 2 + start].repr)
			start = (end - start) / 2 + 1 + start;
		else
			end = (end - start) / 2 - 1 + start;
	}
	if (element.repr >= vec[end].repr)
	{
		std::cout << "true\n";
		std::cout << element.repr << " " << vec[end].repr << std::endl;
		if ((size_t)end == vec.size() - 1)
		{
			vec.push_back(element);
			return ;
		}
		vec.insert(vec.begin() + end + 1, element);
	}
	else if (element.repr < vec[end].repr && element.repr >= vec[start].repr)
		vec.insert(vec.begin() + end, element);
	else
		vec.insert(vec.begin() + start, element);
}

void PmergeMe::insertBOneToAVec (const std::vector<PmergeMe::Group> bSec, 
std::vector<PmergeMe::Group>& aSec)
{
	aSec.insert(aSec.begin(), bSec[0]);
};

void PmergeMe::SplitTheMergedOneLevel(std::vector<PmergeMe::Group>& groups)
{
	for (size_t i = 0; i != groups.size() ; i++)
	{
		if(groups[i].lms.size() == (size_t)spPow(2, this->l))
		{
			Group first;
			Group second;
			for (size_t j = 0; j != groups[i].lms.size(); j++)
			{
				if(j <= groups[i].lms.size() / 2 - 1)
				{
					std::cout << "5\n";
					first.lms.push_back(groups[i].lms[j]);
					printRes(first.lms);
					continue;
				}
				std::cout << "6\n";
				second.lms.push_back(groups[i].lms[j]);
			}
			std::cout << "7\n";
			groups.erase(groups.begin() + i);
			groups.insert(groups.begin() + i, second);
			groups.insert(groups.begin() + i, first);
		}
	}
	std::cout << "1\n";
	this->l--;
}
//=======Outside Functions======================
int	spPow(int n1, int n2)
{
	return ((int)pow((long double)n1, (long double)n2));
};
int jSeq(int n)
{
	return ((spPow(2, n) - spPow(-1, n))/3);
}

void BinarySortOne(std::vector<int>& vec, 
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
	}
	std::cout << "start, end :" << start << ", " << end << std::endl;
	std::cout << "el: " << element << " ,vec[end]: " << vec[end] << " ,vec[start]: " << vec[start] << std::endl;
	

	if (element >= vec[end])
	{
		std::cout << "1\n";
		if ((size_t)end == vec.size() -1)
		{
			std::cout << "2\n";
			vec.push_back(element);
			return ;
		}
		vec.insert(vec.begin() + end + 1, element);
	}
	else if (start != end && element < vec[end] && element >= vec[start])
	{
		std::cout << "3\n";
		vec.insert(vec.begin() + end, element);
	}
	else
	{
		std::cout << "4\n";
		vec.insert(vec.begin() +  start, element);
	}
}

void insertBOneToAVec (const std::vector<int> bSec, 
	std::vector<int>& aSec)
{
	aSec.insert(aSec.begin(), bSec[0]);
}