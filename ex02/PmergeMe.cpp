/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 01:43:30 by tnakas           ###   ########.fr       */
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

//========Checker functions=====================
bool PmergeMe::IsNbr(const std::string& str){return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);};
bool PmergeMe::IsPInt(const std::string& str){return  (std::stod(str) >= 0.0 && std::stod(str) <= 2147483647.0);};

std::vector<int> PmergeMe::fastSort(const std::vector<int> numbers)
{
	std::vector<int> temp = numbers;
	for(size_t i = 0; i != temp.size() - 1; i++)
		for (size_t j = i + 1; j != temp.size(); j++)
			if (temp[i] > temp[j])
				std::swap(temp[i], temp[j]);
	return temp;
}

//========Helper Functions====================
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

//========Logic Fucntions=======================
int PmergeMe::SortingLessThanThree(std::vector<PmergeMe::Group>& vec)
{
	size_t nOfGroupsOnTheSameLevel = 0;
	for (Group& gr : vec)
			if (gr.lms.size() == (size_t)spPow(2, l) && spPow(2,l) != 1)
				nOfGroupsOnTheSameLevel++;
		if (nOfGroupsOnTheSameLevel <= 3)
		{
			for (size_t i = 0; i + 1!=vec.size(); i++)
				for  (size_t j = i + 1; j != vec.size(); j++)
					if (vec[i].repr > vec[j].repr)
						std::swap(vec[i], vec[j]);
			return YES;
		}
		return NO;
};

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
			if (tempGroup[i].lms.size() != tempGroup[i+1].lms.size())
				break;
		}
		l++;
		SortingLessThanThree(tempGroup);
		groups = tempGroup;
	}
	
	return groups;
}

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

void PmergeMe::insertBOneToAVec (std::vector<PmergeMe::Group> bSec, 
std::vector<PmergeMe::Group>& aSec)
{
	aSec.insert(aSec.begin(), bSec[0]);
	bSec.erase(bSec.begin()+ 0);
};

void PmergeMe::SplitTheMergedOneLevel(std::vector<PmergeMe::Group>& groups)
{
	std::vector<Group> newG;
	std::cout << "before in the SplitBOne :";
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
std::vector<int> PmergeMe::sortedVectorOfGroups(std::vector<PmergeMe::Group>& groups)
{
	//maxposition of B is bigger than the max position A I'm starting form the end of the array A
	std::vector<int> res;
	std::vector<std::vector<Group>> pair;
	std::vector<Group> mergedAndSorted;

	mergedAndSorted = pairMergeSorting(groups);
	while(l > 0)
	{
		lastInsPos = 0;
		//- setting the step
		int n, Jn, JnMinusOne, maxPosA;
		n = 3;
		//  split the merged by one
		SplitTheMergedOneLevel(mergedAndSorted);
		//sorting three and If it's true I skip
		if(SortingLessThanThree(mergedAndSorted) == YES) continue;
		// making two pairs
		pair = pairOfBAndA(mergedAndSorted);
		//Inserting the b1 to the the A sequence
		insertBOneToAVec(pair[B], pair[A]);
		lastInsPos=0;
		pair[B].erase(pair[B].begin());
		// computing both jn and jn-1
		
		// routine from jn to jn-1 finding the jn where is on the b if is not existing finding the actual jValue and after
		// after that index of the jValue on the sequence of B after that the index of the actual J on the sequence A
		// if the actual j is not existing in the A 
		// I'm starting from Ajn-1 to end of the A sequence
		// If also jn-1 is not existing I'm starting from 0
		while (!pair[B].empty() && pair[B][0].size ==spPow(2,l))
		{
			Jn = Jacobsthal(n);
			JnMinusOne = Jacobsthal(n - 1) < 0 ? 0 : Jacobsthal(n - 1);
			int indB, indAEnd, indAStart, actualJValue;
			// make different values for current jn and indexOfCurrentJInB jn - i
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
	for (size_t i = 0; i != mergedAndSorted.size() - 1; i++)
		if(!mergedAndSorted[i].lms.empty())
			res.push_back((mergedAndSorted[i].lms[0]));
	return res;
}
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
//=======Outside Functions======================
int	spPow(int n1, int n2){return ((int)pow((long double)n1, (long double)n2));};
int Jacobsthal(int n){return ((spPow(2, n) - spPow(-1, n))/3);};
int spMin(int a, int b){return (a < b ? a : b);}
