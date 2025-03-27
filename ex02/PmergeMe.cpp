/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/27 21:44:39 by tnakas           ###   ########.fr       */
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
	std::cout << "Inside BinarySortOne\n";
	std::cout << "here985\n";
	std::cout << "here985\n";
	std::cout <<" "<< start << " "<< end<<std::endl;
	std::cout << "here985\n";
	std::cout << "here986\n";
	std::cout << (element.lms.size() - 1 == vec[0].lms.size() -1) << std::endl;
	std::cout << "here86\n";
	if (!(element.lms.empty()) && (element.lms.size() - 1 == vec[0].lms.size() -1))
	{
		std::cout << "here85\n";
		std::cout <<" "<< start << " "<< end <<std::endl;
		std::cout << "here85\n";
		std::cout << "here1000\n";
		int first_time = YES;
		while(end - start > 1)
		{
			std::cout << "end - start > 1\n";
			middle = (end - start) /  2 + start;
			std::cout << "here100\n";
			std::cout << "start : " << start << " | middle : " << middle << " | end :" << end << std::endl;
			std::cout << "here101\n";
			std::cout << "here\n";
			std::cout << "start : " << start << " | middle : " << middle << " | end :" << end << std::endl;
			std::cout << "comparisson" << std::endl;
			printRes(element.lms);
			std::cout << " > ";
			printRes(vec[middle].lms);
			std::cout << std::endl;
			if (element.repr > vec[middle].repr)
			{
				std::cout << "start : " << start << " | middle : " << middle << " | end :" << end << std::endl;
				start = middle;
				std::cout << "here57\n";
			}
			else
			{
				std::cout << "here for the first comparisson\n";
				if (first_time == YES)
				{
					std::cout << "here1111\n";
					first_time = NO;
					start = 0;
					std::cout << "start udated to 0\n";
					std::cout << "here1111\n";
				}
				std::cout << "here for the first comparisson\n";
				std::cout << "start : " << start << " | middle : " << middle << " | end :" << end << std::endl;
				std::cout << "here58\n";
				end = middle;
			}

		}
		if(end - start == 1)
		{
			middle = start;
			if (element.repr <= vec[middle].repr)
			{
				if (first_time == YES)
				{
					std::cout << "here2222\n";
					first_time = NO;
					start = 0;
					if (readyToRemove == NO)
						BinarySortOne(vec, start, end - 1, element);
					std::cout << "start udated to 0\n";
					std::cout << "here2222\n";
				}
				protectedInsert(vec, middle, element);
			}
			else if (element.repr > vec[middle].repr && element.repr <= vec[end].repr)
				protectedInsert(vec, middle + 1, element);
			else
			{
				std::cout << "here858\n";
				if (end != (int)vec.size() - 1)
				{
					std::cout << "here758\n";
					std::cout << "start : " << start << " | middle : " << middle << " | end :" << end << std::endl;
					printRes(vec,YES);
					printRes(element.lms);
					protectedInsert(vec, end + 1, element);
					std::cout << "here758\n";
				}
				else
				{
					std::cout << "here658\n";
					protectedPush(vec, element);
					std::cout << "here658\n";
				}
				std::cout << "here858\n";
			}	
		}
		if (end - start == 0)
		{
			middle = start;
			if (element.repr <= vec[start].repr)
			{
				protectedInsert(vec, start, element);
			}
			else
			{
				if (end != (int)vec.size() - 1)
				{
					protectedInsert(vec, start + 1, element);
				}
				else 
				{
					protectedPush(vec, element);
				}
			}
				
		}
	}		
	else
	{
		if (!element.lms.empty())
		{
			vec.push_back(element);
		}
	}
	std::cout << "Inside BinarySortOne\n";
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

std::vector<int> PmergeMe::sortedVectorOfGroups(std::vector<PmergeMe::Group>& groups)
{
	//maxposition of B is bigger than the max position A I'm starting form the end of the array A
	std::vector<int> res;
	std::vector<std::vector<Group>> pair;
	std::vector<Group> mergedAndSorted;

	std::cout << "Before sorted vector: ";
	printRes(groups, NO);
	std::cout << std::endl;
	mergedAndSorted = pairMergeSorting(groups);
	std::cout << "outside of loop" << std::endl;
	printRes(mergedAndSorted, NO);
	std::cout << "outside of loop" << std::endl;
	while(l != 0)
	{
		std::cout << "while(l != 0)\n";
		std::cout << "==> level: "<<  l <<"\n";
		std::cout << "here20\n";
		//- setting the step
		int n = 3;
		//jn and jn-1
		int Jn;
		int JnMinusOne;
		std::cout << " Before SplitTheMergedOneLevel\n";
		printRes(mergedAndSorted, NO);
		SplitTheMergedOneLevel(mergedAndSorted);
		std::cout << " After SplitTheMergedOneLevel\n";
		printRes(mergedAndSorted, NO);
		std::cout << " Before pairOfBAndA(mergedAndSorted)\n";
		pair = pairOfBAndA(mergedAndSorted);
		std::cout << " After pairOfBAndA(mergedAndSorted)\n";
		// int maxPosA = pair[A].size();
		int maxPosB = findMaxIndex(pair[B], B);
		int maxPosA = findMaxIndex(pair[A], A);
		printRes(pair, YES);
		Jn = Jacobsthal(n);
		std::cout << "here6\n";
		JnMinusOne = Jacobsthal(n - 1) < 0 ? 0 : Jacobsthal(n - 1);
		std::cout << "Jn: " << Jn << " | Jn-1: " << JnMinusOne << std::endl;
 		std::cout << "here5\n";
		insertBOneToAVec(pair[B], pair[A]);
		pair[B].erase(pair[B].begin());
		std::cout << "insert and erased the first element\n";
		std::cout << "here5\n";
		while (!pair[B].empty() && pair[B][0].size ==spPow(2,l))
		{
			std::cout << "here10\n";
			std::cout << "here10\n";
			std::cout << "here10\n";
			int indB, indAEnd, indAStart;
			Jn = Jacobsthal(n);
			JnMinusOne = Jacobsthal(n - 1);
			indB = findIndexInPairFromPosition(pair[B], Jn, B);
			std::cout << "here11\n";
			std::cout << "pair[A]";
			printRes(pair[A], NO);
			std::cout << "pair[B]";
			printRes(pair[B], NO);
			std::cout << "Jn: " << Jn;
			std::cout << std::endl;
			std::cout << "here1 \n";
			std::cout << "indB: " << indB <<std::endl;
			//which is the pos of indB
			// in the vector A that is the end
			indAEnd = findIndexInPairFromPosition(pair[A],pair[B][indB].position, A);
			// the begining is the indA
			indAStart = (findIndexInPairFromPosition(pair[A], JnMinusOne, A) == 1) && (indAEnd - 1== 1) ? 0 : findIndexInPairFromPosition(pair[A], JnMinusOne, A);
			while(indB>=0)
			{
				//Binary sorting
				std::cout << "here is the main logic.\n";
				std::cout << "here2 \n";
				printRes(pair, YES);
				std::cout << "indB: " <<  indB << std::endl;
				std::cout << indAStart << " " <<(indAEnd - indAStart)/2 + indAStart   << " " << (pair[B][indB].position > maxPosA ? indAEnd : indAEnd - 1) ;
				printRes(pair[B][indB].lms);
				std::cout << std::endl;
				maxPosB =findMaxIndex(pair[B], B);
				maxPosA =findMaxIndex(pair[A], A);
				std::cout << "pair[B][indB].position > maxPosA ? indAEnd : indAEnd - 1" << " = "<< (pair[B][indB].position > maxPosA ? indAEnd : indAEnd - 1)<<"\n";
				std::cout << pair[B][indB].position<< " > "<<maxPosA<<" ? "<< indAEnd<< " : "<<indAEnd<<" - 1\n";
				std::cout << "here is the main logic.\n";
				std::cout << "start Calling the binary!\n";
				BinarySortOne(pair[A],
					indAStart,
					pair[B][indB].position > maxPosA ? indAEnd : indAEnd - 1, 
					pair[B][indB]);
					std::cout << "finish Calling the binary!\n";
				std::cout << "here3 \n";
				printRes(pair, YES);
				std::cout << "here3 \n";
				protectedErase(pair, indB);
				std::cout << "here4 \n";
				printRes(pair, NO);
				std::cout << "here4 \n";
				std::cout << indB <<std::endl;
				indB--;
			}
			std::cout << "\nhere 9\n";
			std::cout << "n = " << n << std::endl;
			n++;
			std::cout << "n = " << n << std::endl;
			std::cout << "\nhere 9\n";
		}
		while(!pair[B].empty() && pair[B][0].size !=spPow(2,n))
		{
			std::cout << "inside while(!pair[B].empty() && pair[B][0].size !=spPow(2,n))\n after here9\n";
			if (pair[B].empty()) break;
			pair[A].push_back(pair[B][0]);
			pair[B].erase(pair[B].begin());
		}
		printRes(groups, NO);
		mergedAndSorted = pair[A];
		std::cout << "here20\n";
		printRes(groups, NO);
		printRes(pair[A], NO);
		std::cout << "here20\n";
		std::cout << "End Of big Loop\n";
	}
	std::cout << "Next line after l < 0\n";
	std::cout << "here21\n";
	printRes(mergedAndSorted, NO);
	std::cout << "here21\n";
	for (size_t i = 0; i != mergedAndSorted.size() - 1; i++)
	{
		std::cout << "here21\n";
		if(!mergedAndSorted[i].lms.empty())
			res.push_back((mergedAndSorted[i].lms[0]));
		printRes(mergedAndSorted, NO);
	}
	printRes(mergedAndSorted, NO);
	return res;
}

int PmergeMe::findIndexInPairFromPosition(std::vector<PmergeMe::Group> groups, int position, int seq)
{
	int find = NO;
	while (find != YES)
	{
		for (size_t i = 0; i!= groups.size(); i++)
		{
			if (groups[i].position == position && groups[i].sequence == seq)
				return (int)i;
		}
		if (position > 0)
			position--;
		if (position == 0)
			find = YES;
	}
	return -2;
};
int PmergeMe::findMaxIndex(std::vector<PmergeMe::Group> groups, int sqnc)
{
	int  mx = -2147483648;
	for (Group gr : groups)
		if (gr.repr > mx && gr.sequence == sqnc)
			mx = gr.repr;
	int i = 0;
	for (Group gr : groups)
	{
		if (gr.repr == mx && gr.sequence == sqnc)
			break;
		i++;
	}
	return i;
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

// if the Jn - 1
// I don't know how small it is ! so in the first comparisson if the element is lower than the center
// set the begin to zero 
// is m not even getting inside