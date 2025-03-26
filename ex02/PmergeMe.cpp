/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/26 22:53:06 by tnakas           ###   ########.fr       */
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
PmergeMe::Group::Group() : position(0), sequence(0)
{
};
PmergeMe::Group::Group(std::vector<int> lms) : lms(lms), repr(lms.back())
{
};

PmergeMe::Group::Group(const PmergeMe::Group& other)
{
	this->lms = other.lms;
	this->repr = other.repr;
	this->position = other.position;
	this->sequence = other.sequence;
	this->size = other.size;
}
PmergeMe::Group& PmergeMe::Group::operator=(const PmergeMe::Group& other)
{
	if (this != &other)
	{
		this->lms = other.lms;
		this->repr = other.repr;
		this->position = other.position;
		this->sequence = other.sequence;
		this->size = other.size;
	}
	return *this;
}
PmergeMe::Group::~Group(){};


//========Helper Functions====================
void PmergeMe::printRes(const std::vector<int> vec)
{
	std::cout << "[";
	for(int n : vec)
	{
		std::cout << n; 
		if (n != vec[vec.size() -1])
			std::cout << " ";
	}
	std::cout << "]";
}

void PmergeMe::printRes(const std::vector<PmergeMe::Group> groups, int details)
{
	std::cout << "[";
	for (Group gr : groups)
	{
		std::cout << "[";
		printRes(gr.lms);
		if (details == YES)
		{
			std::cout << "|size:" << gr.size << "|"<< "repr:" << gr.repr <<  "|pos:"<< gr.position << "|" << "seq:"<<  gr.sequence;
		}
		std::cout << "]  ";
	}
	std::cout << "]";
	std::cout << std::endl;
}
void PmergeMe::printRes(const std::vector<std::vector<PmergeMe::Group>> pair , int details)
{
	std::cout << "A sequence: ";
	printRes(pair[0], details);
	std::cout << "B sequence: ";
	printRes(pair[1], details);
};
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
		std::vector<Group> tempGroup;
		for (size_t i = 0; i + 1 < groups.size(); i+=2)
		{
			std::vector<int> mergedElemets = groups[i].lms;
			mergedElemets.insert(mergedElemets.end(),
			groups[i + 1].lms.begin(), 
			groups[i + 1].lms.end());
			tempGroup.emplace_back(mergedElemets);
		}
		if (groups.size() % 2 != 0)
			tempGroup.emplace_back(groups[groups.size() - 1].lms);
		for (size_t i = 0; i + 1 < tempGroup.size(); i+=2)
			if (tempGroup[i].repr > tempGroup[i + 1].repr && tempGroup[i].lms.size() == tempGroup[i + 1].lms.size())
				std::swap(tempGroup[i], tempGroup[i + 1]);
	groups = tempGroup;
	l++;
	std::cout << "Level: "<< l << std::endl;
	}
	
	return groups;
}

void PmergeMe::BinarySortOne(std::vector<Group>& vec, 
	int start, int end, Group element)
{
	int middle = -1;
	if (element.lms.size() -1 == vec[0].lms.size() -1)
	{
		while(end - start != 1)
		{
			middle = (end - start) /  2 + start;
			if (element.lms[element.lms.size() - 1] > vec[middle].lms[vec[middle].lms.size() - 1])
				start = middle;
			else
				end = middle;
		}
	
		if (element.lms[element.lms.size() - 1] <= vec[middle].lms[vec[middle].lms.size() - 1])
				vec.insert(vec.begin() + middle, element);
		else
		{
			if (end !=(int)vec.size() - 1)
				vec.insert(vec.begin() + middle + 1, element);
			else
				vec.push_back(element);
		}
	}		
	else
		vec.push_back(element);
}

void PmergeMe::insertBOneToAVec (std::vector<PmergeMe::Group> bSec, 
std::vector<PmergeMe::Group>& aSec)
{
	aSec.insert(aSec.begin(), bSec[0]);
	bSec.erase(bSec.begin()+ 0);
};

void PmergeMe::SplitTheMergedOneLevel(std::vector<PmergeMe::Group>& groups)
{
	std::vector<Group> newG;
	// std::cout << "before in the SplitBOne :";
	// printRes(groups);
	for (size_t i = 0; i != groups.size() ; i++)
	{
		if(groups[i].lms.size() <= (size_t)spPow(2, l) && groups[i].lms.size() >  (size_t)spPow(2, l - 1))
		{
			Group first;
			Group second;
			size_t mid = groups[i].lms.size() / 2;
			for (size_t j = 0; j != groups[i].lms.size(); j++)
			{
				if(j < mid || (j == mid && groups[i].lms.size() %2 != 0))
					first.lms.push_back(groups[i].lms[j]);
				else
					second.lms.push_back(groups[i].lms[j]);
			}
			newG.push_back(first);
			newG.push_back(second);
		}
		else
			newG.push_back(groups[i]);
	}
	l--;
	groups = newG;
}

std::vector<std::vector<PmergeMe::Group>> PmergeMe::pairOfBAndA(std::vector<PmergeMe::Group> groups)
{
	std::vector<std::vector<Group>> pair;
	std::vector<Group> a;
	std::vector<Group> b;
	int a_position = 1;
	int b_position = 1;
	pair.push_back(a);
	pair.push_back(b);
	size_t NumberElemsWithSameSize = 0;
	size_t i;
	while (groups[NumberElemsWithSameSize].lms.size() == (size_t)spPow(2, l))
		NumberElemsWithSameSize++;
	if (NumberElemsWithSameSize <= 3)
			for (size_t j = 0; j + 1!= NumberElemsWithSameSize; j++)
				for (size_t z = j + 1; z!= NumberElemsWithSameSize; z++)
					if (groups[j].repr > groups[z].repr)
						std::swap(groups[j], groups[z]);
	for (i = 0; i != groups.size(); i++)
	{
		groups[i].repr = groups[i].lms[groups[i].lms.size() -1];
		groups[i].size = groups[i].lms.size();
		if (groups[i].lms.size() == (size_t)spPow(2, l))
		{
			if ( i % 2 != 0)
			{
				groups[i].sequence = A;
				groups[i].position = a_position++;
				pair[A].push_back(groups[i]);
			}
			else
			{
				groups[i].sequence = B;
				groups[i].position = b_position++;
				pair[B].push_back(groups[i]);
			}
		}
		else
		{
			groups[i].position = -2;
			pair[B].push_back(groups[i]);
		}
	}
	return pair;
};
int PmergeMe::findIndexInPairFromPosition(std::vector<PmergeMe::Group> groups, int position)
{
	int find = NO;
	while (find != YES)
	{
		size_t i = 0;
		for (Group gr : groups)
		{
			i++;
			if (gr.position == position)
				return (int)i;
		}
		if (position > 0)
			position--;
		if (position == 0)
			find = YES;
	}
	return -2;
};
std::vector<int> PmergeMe::sortedVectorOfGroups(std::vector<PmergeMe::Group>& groups)
{
	std::vector<int> res;
	std::vector<std::vector<Group>> pair;
	std::vector<Group> mergedAndSorted;

	// std::cout << "Before sorted vector: ";
	printRes(groups, NO);
	std::cout << std::endl;
	mergedAndSorted = pairMergeSorting(groups);
	printRes(mergedAndSorted, NO);
	while(l != 0)
	{
		//- setting the step
		int n = 3;
		//jn and jn-1
		int Jn;
		int JnMinusOne;
		SplitTheMergedOneLevel(mergedAndSorted);
		pair = pairOfBAndA(mergedAndSorted);
		// int maxPosA = pair[A].size();
		int maxPosB = 0;
		for (Group gr : pair[B])
			if (gr.size == spPow(2, l))
				maxPosB++;
		Jn = Jacobsthal(n) < maxPosB ? Jacobsthal(n) : maxPosB;
		std::cout << "here6\n";
		JnMinusOne = Jacobsthal(n - 1);
		std::cout << "here5\n";
		while (pair[B].size() != 0 && pair[B][0].size ==spPow(2,l))
		{
			insertBOneToAVec(pair[B], pair[A]);
			pair[B].erase(pair[B].begin());
			int indB;
			indB = findIndexInPairFromPosition(pair[B], Jn);
			std::cout << "here1 \n";
			while(indB>=0)
			{
				//Binary sorting
				std::cout << "here2 \n";
				BinarySortOne(pair[A],
					findIndexInPairFromPosition(pair[A], JnMinusOne),
					findIndexInPairFromPosition(pair[A], Jn) - 1, 
					pair[B][indB]);
				std::cout << "here3 \n";
				pair[B].erase(pair[B].begin() + indB);
				std::cout << "here4 \n";
				indB--;
			}
		}
		while(pair[B].size() != 0 && pair[B][0].size !=spPow(2,n))
		{
			pair[A].push_back(pair[B][0]);
			pair[B].erase(pair[B].begin());
		}
		groups = pair[A];
	}
	for (size_t i = 0; i != groups.size() - 1; i++)
		res[i] = groups[i].lms[0];
	printRes(groups, NO);
	return res;
}
//=======Outside Functions======================
int	spPow(int n1, int n2)
{
	return ((int)pow((long double)n1, (long double)n2));
};
int Jacobsthal(int n)
{
	return ((spPow(2, n) - spPow(-1, n))/3);
}
int spMin(int a, int b)
{
	return (a < b ? a : b);
}