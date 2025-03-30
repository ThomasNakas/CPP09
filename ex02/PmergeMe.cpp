/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 05:42:49 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
//========PmergeMe Default Functions=========
PmergeMe::PmergeMe(){};
PmergeMe::~PmergeMe(){};
PmergeMe::PmergeMe(const PmergeMe& other){*this = other;};
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
};
//========Group Default Functions=============
PmergeMe::Group::Group() : position(0), sequence(0){};
PmergeMe::Group::Group(std::vector<int> lms) : lms(lms), repr(lms.back()){};
PmergeMe::Group::Group(std::deque<int> lmsD) : lmsD(lmsD), repr(lmsD.back()){};

PmergeMe::Group::Group(const PmergeMe::Group& other)
{
	this->lms = other.lms;
	this->lmsD = other.lmsD;
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
		this->lmsD = other.lmsD;
		this->repr = other.repr;
		this->position = other.position;
		this->sequence = other.sequence;
		this->size = other.size;
	}
	return *this;
}
PmergeMe::Group::~Group(){};

//========Checker functions=====================
bool PmergeMe::IsNbr(const std::string& str){return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);};
bool PmergeMe::IsPInt(const std::string& str){return  (std::stod(str) >= 0.0 && std::stod(str) <= 2147483647.0);};
//========Input Validation======================
int PmergeMe::inputIsValid (char* argv[], int argc)
{
	if (argc < 2)
	{
		std::cerr << "Error: No input provided.\n";
		return NO;
	}
	for (int i = 1; i < argc; i++)
	{
		if (!IsNbr(argv[i]) || !IsPInt(argv[i]))
		{
			std::cerr 
			<< "Error: arguments needs to be possitive (or equal with zero) integers\n";
			return NO;
		}
	}
	return YES;
}
std::vector<int> PmergeMe::fastSort(const std::vector<int> numbers)
{
	std::vector<int> temp = numbers;
	for(size_t i = 0; i != temp.size() - 1; i++)
		for (size_t j = i + 1; j != temp.size(); j++)
			if (temp[i] > temp[j])
				std::swap(temp[i], temp[j]);
	return temp;
}
std::deque<int> PmergeMe::fastSort(const std::deque<int> numbers)
{
	std::deque<int> temp = numbers;
	for(size_t i = 0; i != temp.size() - 1; i++)
		for (size_t j = i + 1; j != temp.size(); j++)
			if (temp[i] > temp[j])
				std::swap(temp[i], temp[j]);
	return temp;
}
//==Prinmary functions==========================
//----->vectors<-------
std::vector<int> PmergeMe::primaryVec(char* argv[], int argc)
{
	std::vector<PmergeMe::Group> groups;
	std::vector<int> numbers;
	std::vector<int> res;

	for (int i = 1; i < argc; i++)
		numbers.push_back(std::stoi(argv[i]));
	if (numbers.size() == 3)
		for (size_t i = 0; i + 1 != numbers.size(); i++)
			for (size_t j = i; j != numbers.size(); j++)
				if (numbers[i] > numbers[j])
					std::swap(numbers[i], numbers[j]);
	for (size_t i =0; i + 1 < numbers.size(); i+=2)
		if (numbers[i] > numbers[i + 1])
			std::swap(numbers[i], numbers[i + 1]);
	for (size_t i = 0; i < numbers.size(); i++)
		groups.emplace_back(std::vector<int>{numbers[i]});
	res = sortedVectorOfGroups(groups);
	return res;
};
std::deque<int> PmergeMe::primaryDeq(char* argv[], int argc)
{
	std::deque<PmergeMe::Group> groupsD;
	std::deque<int> numbersD;
	std::deque<int> resD;
	for (int i = 1; i < argc; i++)
		numbersD.push_back(std::stoi(argv[i]));
	if (numbersD.size() == 3)
		for (size_t i = 0; i + 1 != numbersD.size(); i++)
			for (size_t j = i; j != numbersD.size(); j++)
				if (numbersD[i] > numbersD[j])
					std::swap(numbersD[i], numbersD[j]);
	for (size_t i =0; i + 1 < numbersD.size(); i+=2)
		if (numbersD[i] > numbersD[i + 1])
			std::swap(numbersD[i], numbersD[i + 1]);
	for (size_t i = 0; i < numbersD.size(); i++)
		groupsD.emplace_back(std::vector<int>{numbersD[i]});

	l = 0; lastInsPos = -1; minIns = 2147483647;
	resD = sortedDequeOfGroups(groupsD);
	return resD;
};
//----->deques<--------
//========Helper Functions======================
//----->vectors<-------
void PmergeMe::printRes(const std::vector<int> vec)
{
	std::cout << "[";
	for(int n : vec)
	{
		std::cout << n; 
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
		std::cout << "|size:" << gr.size << "|"<< "repr:" << gr.repr <<  "|pos:"<< gr.position << "|" << "seq:"<<  gr.sequence;
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
	std::cout << std::endl;
};
//----->deques<--------
void PmergeMe::printRes(const std::deque<int> dq)
{
	std::cout << "[";
	for(int n : dq)
	{
		std::cout << n; 
		std::cout << " ";
	}
	std::cout << "]";
}

void PmergeMe::printRes(const std::deque<PmergeMe::Group> groups, int details)
{
	std::cout << "[";
	for (Group gr : groups)
	{
		std::cout << "[";
		printRes(gr.lms);
		if (details == YES)
			std::cout << "|size:" << gr.size << "|"<< "repr:" << gr.repr <<  "|pos:"<< gr.position << "|" << "seq:"<<  gr.sequence;
		std::cout << "]  ";
	}
	std::cout << "]";
	std::cout << std::endl;
}
void PmergeMe::printRes(const std::deque<std::deque<PmergeMe::Group>> pair , int details)
{
	std::cout << "A sequence: ";
	printRes(pair[0], details);
	std::cout << "B sequence: ";
	printRes(pair[1], details);
	std::cout << std::endl;
};


//========Logic Fucntions=======================
//========Sorting Less Than Three===============
//----->vectors<-------
int PmergeMe::SortingLessThanThree(std::vector<PmergeMe::Group>& vec)
{
	size_t nOfGroupsOnTheSameLevel = 0;
	for (Group& gr : vec)
			if (gr.lms.size() == (size_t)spPow(2, l) && spPow(2,l) != 1)
				nOfGroupsOnTheSameLevel++;
		if (nOfGroupsOnTheSameLevel <= 3)
		{
			for (size_t i = 0; i + 1!=nOfGroupsOnTheSameLevel; i++)
				for  (size_t j = i + 1; j != nOfGroupsOnTheSameLevel; j++)
					if (vec[i].repr > vec[j].repr)
						std::swap(vec[i], vec[j]);
			return YES;
		}
		return NO;
};
//----->deques<--------
int PmergeMe::SortingLessThanThree(std::deque<PmergeMe::Group>& dq)
{
	size_t nOfGroupsOnTheSameLevel = 0;
	for (Group& gr : dq)
			if (gr.lms.size() == (size_t)spPow(2, l) && spPow(2,l) != 1)
				nOfGroupsOnTheSameLevel++;
		if (nOfGroupsOnTheSameLevel <= 3)
		{
			for (size_t i = 0; i + 1!=nOfGroupsOnTheSameLevel; i++)
				for  (size_t j = i + 1; j != nOfGroupsOnTheSameLevel; j++)
					if (dq[i].repr > dq[j].repr)
						std::swap(dq[i], dq[j]);
			return YES;
		}
		return NO;
};
//========Helper Pairing and Internal Sorting===
//----->vectors<-------
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
		{
			if (tempGroup[i].repr > tempGroup[i + 1].repr && tempGroup[i].lms.size() == tempGroup[i + 1].lms.size())
				std::swap(tempGroup[i], tempGroup[i + 1]);
		}
		l++;
		SortingLessThanThree(tempGroup);
		groups = tempGroup;
	}
	
	return groups;
}
//----->deques<--------
std::deque<PmergeMe::Group> PmergeMe::pairMergeSorting(std::deque<PmergeMe::Group> groups)
{
	while (groups.size() > 3)
	{
		std::deque<Group> tempGroup;
		for (size_t i = 0; i + 1 < groups.size(); i+=2)
		{
			std::deque<int> mergedElemets = groups[i].lmsD;
			mergedElemets.insert(mergedElemets.end(),
			groups[i + 1].lmsD.begin(), 
			groups[i + 1].lmsD.end());
			tempGroup.emplace_back(mergedElemets);
		}
		if (groups.size() % 2 != 0)
			tempGroup.emplace_back(groups[groups.size() - 1].lmsD);
		for (size_t i = 0; i + 1 < tempGroup.size(); i+=2)
		{
			if (tempGroup[i].repr > tempGroup[i + 1].repr && tempGroup[i].lmsD.size() == tempGroup[i + 1].lmsD.size())
				std::swap(tempGroup[i], tempGroup[i + 1]);
		}
		l++;
		SortingLessThanThree(tempGroup);
		groups = tempGroup;
	}
	
	return groups;
}
//========Binary Sorting One====================
//----->vectors<-------
void PmergeMe::BinarySortOne(std::vector<Group>& vec, 
	int start, int end, Group element)
{
	int middle = -1;
	if (!(element.lms.empty()) && (element.lms.size() == (size_t)spPow(2, l)))
	{
		while(end - start > 1)
		{
			middle = (end - start) /  2 + start;
			if (element.repr > vec[middle].repr)
				start = middle;
			else
				end = middle;
		}
		if (element.repr <= vec[start].repr)
		{
			while (start > 0 && (vec[start].repr == vec[start - 1].repr))
				start--;
			vec.insert(vec.begin() + start,element);
		}
		else if (element.repr > vec[start].repr && element.repr <= vec[end].repr)
		{
			while (start < (int)vec.size() - 2 && vec[start].repr == vec[start + 1].repr)
				start++;
			while (end > 1 && vec[end].repr == vec[end - 1].repr)
				end--;
			vec.insert(vec.begin() + start + 1,element);
		}
		else
		{
			while (end !=(int)vec.size() - 2 && vec[end].repr == vec[end + 1].repr)
				end++;
			if (end != (int)vec.size() - 1)
				vec.insert(vec.begin() + end + 1 ,element);
			else
				vec.push_back(element);
		}
		if (vec[lastInsPos].repr > element.repr)
			lastInsPos = findIndexInPairFromPosition(vec, element.position, B);
	}		
	else
		if (!element.lms.empty())
			vec.push_back(element);
}
//----->deques<--------
void PmergeMe::BinarySortOne(std::deque<Group>& dq, 
	int start, int end, Group element)
{
	int middle = -1;
	if (!(element.lms.empty()) && (element.lms.size() == (size_t)spPow(2, l)))
	{
		while(end - start > 1)
		{
			middle = (end - start) /  2 + start;
			if (element.repr > dq[middle].repr)
				start = middle;
			else
				end = middle;
		}
		if (element.repr <= dq[start].repr)
		{
			while (start > 0 && (dq[start].repr == dq[start - 1].repr))
				start--;
			dq.insert(dq.begin() + start,element);
		}
		else if (element.repr > dq[start].repr && element.repr <= dq[end].repr)
		{
			while (start < (int)dq.size() - 2 && dq[start].repr == dq[start + 1].repr)
				start++;
			while (end > 1 && dq[end].repr == dq[end - 1].repr)
				end--;
			dq.insert(dq.begin() + start + 1,element);
		}
		else
		{
			while (end !=(int)dq.size() - 2 && dq[end].repr == dq[end + 1].repr)
				end++;
			if (end != (int)dq.size() - 1)
				dq.insert(dq.begin() + end + 1 ,element);
			else
				dq.push_back(element);
		}
		if (dq[lastInsPos].repr > element.repr)
			lastInsPos = findIndexInPairFromPosition(dq, element.position, B);
	}		
	else
		if (!element.lms.empty())
			dq.push_back(element);
}
//========Inserting b1 to A sequence============
//----->vectors<-------
void PmergeMe::insertBOneToAVec (std::vector<PmergeMe::Group> bSec, std::vector<PmergeMe::Group>& aSec)
{
	aSec.insert(aSec.begin(), bSec[0]);
	bSec.erase(bSec.begin()+ 0);
};
//----->deques<--------
void PmergeMe::insertBOneToAVec (std::deque<PmergeMe::Group> bSecD, std::deque<PmergeMe::Group>& aSecD)
{
	aSecD.insert(aSecD.begin(), bSecD[0]);
	bSecD.erase(bSecD.begin()+ 0);
};
//========Helper Functions======================
//========Spliting the Merge One Level==========
//----->vectors<-------
void PmergeMe::SplitTheMergedOneLevel(std::vector<PmergeMe::Group>& groups)
{
	std::vector<Group> newG;
	for (size_t i = 0; i != groups.size() ; i++)
	{
		if(groups[i].lms.size() <= (size_t)spPow(2, l) && groups[i].lms.size() >  (size_t)spPow(2, l - 1))
		{
			Group first;
			Group second;
			size_t mid = (size_t)spPow(2,l - 1);
			for (size_t j = 0; j != mid; j++)
					first.lms.push_back(groups[i].lms[j]);
			for (size_t j = mid; j != groups[i].lms.size(); j++)
					second.lms.push_back(groups[i].lms[j]);
			newG.push_back(first);
			newG.push_back(second);
		}
		else
			newG.push_back(groups[i]);
	}
	l--;
	if (l >= 0)
	{
		
		for (Group& gr : newG)
		{
			if(gr.lms.size() ==(size_t)spPow(2, l))
			{
				gr.size = gr.lms.size();
				gr.repr = gr.lms[gr.size - 1];
			}
		}
	}
	groups = newG;
}
//----->deques<--------
void PmergeMe::SplitTheMergedOneLevel(std::deque<PmergeMe::Group>& groups)
{
	std::deque<Group> newG;
	for (size_t i = 0; i != groups.size() ; i++)
	{
		if(groups[i].lmsD.size() <= (size_t)spPow(2, l) && groups[i].lmsD.size() >  (size_t)spPow(2, l - 1))
		{
			Group first;
			Group second;
			size_t mid = (size_t)spPow(2,l - 1);
			for (size_t j = 0; j != mid; j++)
					first.lmsD.push_back(groups[i].lmsD[j]);
			for (size_t j = mid; j != groups[i].lmsD.size(); j++)
					second.lmsD.push_back(groups[i].lmsD[j]);
			newG.push_back(first);
			newG.push_back(second);
		}
		else
			newG.push_back(groups[i]);
	}
	l--;
	if (l >= 0)
	{
		
		for (Group& gr : newG)
		{
			if(gr.lms.size() ==(size_t)spPow(2, l))
			{
				gr.size = gr.lms.size();
				gr.repr = gr.lms[gr.size - 1];
			}
		}
	}
	groups = newG;
}
//========Creating Pairing Sequences============
//----->vectors<-------
std::vector<std::vector<PmergeMe::Group>> PmergeMe::pairOfBAndA(std::vector<PmergeMe::Group> groups)
{
	std::vector<std::vector<Group>> pair;
	std::vector<Group> a;
	std::vector<Group> b;
	int a_position = 1;
	int b_position = 1;
	pair.push_back(a);
	pair.push_back(b);
	for (size_t i = 0; i != groups.size(); i++)
	{
		if (groups[i].lms.size() == (size_t)spPow(2, l))
		{
			groups[i].position = 0;
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
//----->deques<--------
std::deque<std::deque<PmergeMe::Group>> PmergeMe::pairOfBAndA(std::deque<PmergeMe::Group> groups)
{
	std::deque<std::deque<Group>> pair;
	std::deque<Group> a;
	std::deque<Group> b;
	int a_position = 1;
	int b_position = 1;
	pair.push_back(a);
	pair.push_back(b);
	for (size_t i = 0; i != groups.size(); i++)
	{
		if (groups[i].lms.size() == (size_t)spPow(2, l))
		{
			groups[i].position = 0;
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
//========Implementing the Binary Sorting ======
//========per Jn-1 Jn indexes===================
//----->vectors<-------
std::vector<int> PmergeMe::sortedVectorOfGroups(std::vector<PmergeMe::Group>& groups)
{
	std::vector<int> res;
	std::vector<std::vector<Group>> pair;
	std::vector<Group> mergedAndSorted;

	mergedAndSorted = pairMergeSorting(groups);
	while(l > 0)
	{
		lastInsPos = 0;
		int n, Jn, JnMinusOne, maxPosA;
		n = 3;
		SplitTheMergedOneLevel(mergedAndSorted);
		pair = pairOfBAndA(mergedAndSorted);
		insertBOneToAVec(pair[B], pair[A]);
		lastInsPos=0;
		pair[B].erase(pair[B].begin());
		while (!pair[B].empty() && pair[B][0].size ==spPow(2,l))
		{
			Jn = Jacobsthal(n);
			JnMinusOne = Jacobsthal(n - 1) < 0 ? 0 : Jacobsthal(n - 1);
			int indB, indAEnd, indAStart, actualJValue;
			indB = findIndexInPairFromPosition(pair[B], Jn, B);
			actualJValue = pair[B][indB].position;
			maxPosA = findMaxPos(pair[A], A);
			while(indB>=0)
			{
				indAEnd = findIndexInPairFromPosition(pair[A], actualJValue, A) - 1;
				if (maxPosA < actualJValue)
					indAEnd = pair[A].size() - 1;
				indAStart =  std::min((lastInsPos - 1 > 0)? lastInsPos - 1 : 0, findIndexInPairFromPosition(pair[A], JnMinusOne, A));
				if (maxPosA < JnMinusOne)
					indAStart = 0;
				while(indAStart > 0 && pair[A][indAStart].repr == pair[A][indAStart - 1].repr)
					indAStart--;
				while(indAEnd<(int)pair[A].size() - 1 && pair[A][indAEnd].repr == pair[A][indAEnd + 1].repr)
					indAEnd++;
				BinarySortOne(pair[A], indAStart, indAEnd, pair[B][indB]);
				pair[B].erase(pair[B].begin() + indB);
				actualJValue--;
				indB = findIndexInPairFromPosition(pair[B], actualJValue, B);
			}
			n++;
		}
		while(!pair[B].empty() && pair[B][0].size !=spPow(2,n))
		{
			if (pair[B].empty()) break;
			pair[A].push_back(pair[B][0]);
			pair[B].erase(pair[B].begin());
		}
		mergedAndSorted = pair[A];
	}
	for (size_t i = 0; i != mergedAndSorted.size(); i++)
		if(!mergedAndSorted[i].lms.empty())
			res.push_back((mergedAndSorted[i].lms[0]));
	return res;
}
//----->deques<--------
std::deque<int> PmergeMe::sortedDequeOfGroups(std::deque<PmergeMe::Group>& groups)
{
	std::deque<int> resD;
	std::deque<std::deque<Group>> pair;
	std::deque<Group> mergedAndSorted;

	mergedAndSorted = pairMergeSorting(groups);
	while(l > 0)
	{
		lastInsPos = 0;
		int n, Jn, JnMinusOne, maxPosA;
		n = 3;
		SplitTheMergedOneLevel(mergedAndSorted);
		pair = pairOfBAndA(mergedAndSorted);
		insertBOneToAVec(pair[B], pair[A]);
		lastInsPos=0;
		pair[B].erase(pair[B].begin());
		while (!pair[B].empty() && pair[B][0].size ==spPow(2,l))
		{
			Jn = Jacobsthal(n);
			JnMinusOne = Jacobsthal(n - 1) < 0 ? 0 : Jacobsthal(n - 1);
			int indB, indAEnd, indAStart, actualJValue;
			indB = findIndexInPairFromPosition(pair[B], Jn, B);
			actualJValue = pair[B][indB].position;
			maxPosA = findMaxPos(pair[A], A);
			while(indB>=0)
			{
				indAEnd = findIndexInPairFromPosition(pair[A], actualJValue, A) - 1;
				if (maxPosA < actualJValue)
					indAEnd = pair[A].size() - 1;
				indAStart =  std::min((lastInsPos - 1 > 0)? lastInsPos - 1 : 0, findIndexInPairFromPosition(pair[A], JnMinusOne, A));
				if (maxPosA < JnMinusOne)
					indAStart = 0;
				while(indAStart > 0 && pair[A][indAStart].repr == pair[A][indAStart - 1].repr)
					indAStart--;
				while(indAEnd<(int)pair[A].size() - 1 && pair[A][indAEnd].repr == pair[A][indAEnd + 1].repr)
					indAEnd++;
				BinarySortOne(pair[A], indAStart, indAEnd, pair[B][indB]);
				pair[B].erase(pair[B].begin() + indB);
				actualJValue--;
				indB = findIndexInPairFromPosition(pair[B], actualJValue, B);
			}
			n++;
		}
		while(!pair[B].empty() && pair[B][0].size !=spPow(2,n))
		{
			if (pair[B].empty()) break;
			pair[A].push_back(pair[B][0]);
			pair[B].erase(pair[B].begin());
		}
		mergedAndSorted = pair[A];
	}
	for (size_t i = 0; i != mergedAndSorted.size(); i++)
		if(!mergedAndSorted[i].lms.empty())
			resD.push_back((mergedAndSorted[i].lms[0]));
	return resD;
}
//========Helpers for vectors===================
int PmergeMe::findIndexInPairFromPosition(std::vector<PmergeMe::Group> groups, int position, int seq)
{
	while (position > 0)
	{
		for (size_t i = 0; i!= groups.size(); i++)
			if (groups[i].position == position && groups[i].sequence == seq)
				return (int)i;
		position --;
	}
	return -1;
};
int PmergeMe::findMaxIndex(std::vector<PmergeMe::Group> groups, int sqnc, int mx)
{
	int i = 0;
	for (Group gr : groups)
	{
		if (gr.repr == mx && gr.sequence == sqnc)
			break;
		i++;
	}
	return i;
};
int PmergeMe::findMaxPos(std::vector<PmergeMe::Group> groups, int sqnc)
{
	int  mx = -2147483648;
	for (Group gr : groups)
		if (gr.repr > mx && gr.sequence == sqnc)
			mx = gr.position;
	return mx;
};

void 	PmergeMe::protectedInsert(std::vector<PmergeMe::Group>& vec, int start, PmergeMe::Group element)
{
	if (readyToRemove == NO)
	{
		vec.insert(vec.begin() + start, element);
		readyToRemove = YES;
	}
};
void 	PmergeMe::protectedPush(std::vector<PmergeMe::Group>& vec, PmergeMe::Group element)
{
	if (readyToRemove == NO)
	{
		vec.push_back(element);
		readyToRemove = YES;
	}
};
void PmergeMe::protectedErase(std::vector<std::vector<PmergeMe::Group>>& pair, int index)
{ 
	pair[B].erase(pair[B].begin() + index);
	readyToRemove = NO;
};
int	PmergeMe::jacobsthalIsExisitng(std::vector<PmergeMe::Group> gr, int jacobsthal)
{
	for (size_t i = 0; i != gr.size(); i++)
		if (gr[i].repr == jacobsthal)
			return YES;
	return NO;
}
//========Helpers for deques====================
int PmergeMe::findIndexInPairFromPosition(std::deque<PmergeMe::Group> groups, int position, int seq)
{
	while (position > 0)
	{
		for (size_t i = 0; i!= groups.size(); i++)
			if (groups[i].position == position && groups[i].sequence == seq)
				return (int)i;
		position --;
	}
	return -1;
};
int PmergeMe::findMaxIndex(std::deque<PmergeMe::Group> groups, int sqnc, int mx)
{
	int i = 0;
	for (Group gr : groups)
	{
		if (gr.repr == mx && gr.sequence == sqnc)
			break;
		i++;
	}
	return i;
};
int PmergeMe::findMaxPos(std::deque<PmergeMe::Group> groups, int sqnc)
{
	int  mx = -2147483648;
	for (Group gr : groups)
		if (gr.repr > mx && gr.sequence == sqnc)
			mx = gr.position;
	return mx;
};

void 	PmergeMe::protectedInsert(std::deque<PmergeMe::Group>& vec, int start, PmergeMe::Group element)
{
	if (readyToRemove == NO)
	{
		vec.insert(vec.begin() + start, element);
		readyToRemove = YES;
	}
};
void 	PmergeMe::protectedPush(std::deque<PmergeMe::Group>& vec, PmergeMe::Group element)
{
	if (readyToRemove == NO)
	{
		vec.push_back(element);
		readyToRemove = YES;
	}
};
void PmergeMe::protectedErase(std::deque<std::deque<PmergeMe::Group>>& pair, int index)
{ 
	pair[B].erase(pair[B].begin() + index);
	readyToRemove = NO;
};
int	PmergeMe::jacobsthalIsExisitng(std::deque<PmergeMe::Group> gr, int jacobsthal)
{
	for (size_t i = 0; i != gr.size(); i++)
		if (gr[i].repr == jacobsthal)
			return YES;
	return NO;
}
//=======Outside Functions======================
int	spPow(int n1, int n2){return ((int)pow((long double)n1, (long double)n2));};
int Jacobsthal(int n){return ((spPow(2, n) - spPow(-1, n))/3);};
int spMin(int a, int b){return (a < b ? a : b);}
