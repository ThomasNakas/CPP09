/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:47 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/26 19:48:20 by tnakas           ###   ########.fr       */
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
}
PmergeMe::Group& PmergeMe::Group::operator=(const PmergeMe::Group& other)
{
	if (this != &other)
	{
		this->lms = other.lms;
		this->repr = other.repr;
		this->position = other.position;
		this->sequence = other.sequence;
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
			std::cout << " | pos : "<< gr.position << " " << "seq: "<<  gr.sequence;
		std::cout << "]";
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
	// printRes(groups);
	l++;
	std::cout << "Level: "<< l << std::endl;
	// std::cout << "the size: " << tempGroup.size() << std::endl;
	}
	
	return groups;
}

void PmergeMe::BinarySortOne(std::vector<Group>& vec, 
	int start, int end, Group element)
{
	int middle = -1;
	// std::cout << "start = 0" << "real : " << start << std::endl;
	// std::cout << "end = 3" << "real : " << end << std::endl;
	// printRes(vec, NO);
	// printRes(element.lms);
	// std::cout<<std::endl;
	if (element.lms.size() -1 == vec[0].lms.size() -1)
	{
		while(end - start != 1)
		{
			// i++;
			// if (i == 12)
			// 	break;
			// std::cout << "making the " << i <<std::endl;
			middle = (end - start) /  2 + start;
			// std::cout << "start : middle :  end ->" <<std::endl;
			// std::cout << start << " : " << middle << " : "<< end << std::endl;
			// std::cout << element.lms[element.lms.size() - 1] << ". . ."<< vec[middle].lms[vec[middle].lms.size() - 1]<<std::endl;
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
	// std::cout << "Before in Pair Of B :" ;
	// printRes(groups);
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
	size_t i = 0;
	for (Group gr : groups)
	{
		i++;
		if (gr.position == position)
			return (int)i;
		
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
		int n = 0;
		// int n = 3;
		// pairMergeSorting
		// std::cout << "Step 1\n";
		SplitTheMergedOneLevel(mergedAndSorted);
		printRes(mergedAndSorted, NO);
		// pair a , b sequence
		// std::cout << "Step 2\n";
		pair = pairOfBAndA(mergedAndSorted);
		// printRes(pair, NO);
		// std::cout << "Step 3\n";
		insertBOneToAVec(pair[B], pair[A]);
		pair[B].erase(pair[B].begin());
		printRes(pair, NO);
		// I ll print the jabobsthal frequences
		while (++n < 20)
		{
			int reverse, prev;
			reverse = spMin(Jacobsthal(n), (int)pair[B].size() - 1);
			prev = spMin(Jacobsthal(n - 1), 0);
			std::cout << std::endl;
			std::cout << "from B: \n";
			for (int i = reverse; i >= prev; i--)
			{
				// std::cout << pair[B][i].lms.size() << std::endl;
				if ((int)pair[B][i].lms.size() == spPow(2, l))
					printRes(pair[B][i].lms);
			}
			std::cout << std::endl;
		}
		std::cout <<std::endl;
		while (pair[B].size() != 0)
		{
			BinarySortOne(pair[A], 0, (int)pair[A].size(), pair[B][0]);
			pair[B].erase(pair[B].begin());
		}
	}
	
	res.push_back(0);
	return res;
}






	
		// int n = 3;
		// int J;
		// int maxBIndexSequence, maxAIndexSequence, notReady;
		// std::vector<Group> a,b;
		// SplitTheMergedOneLevel(groups);
		// pair = pairOfBAndA(groups);
		// a = pair[A];
		// b = pair[B];
		// notReady = 0;
		// for (size_t i = 0; i !=pair[B].size(); i++)
		// 	if (pair[B][i].lms.size() != (size_t)spPow(2, l))
		// 		notReady++;
		// maxBIndexSequence = pair[A].size() - notReady;
		// maxAIndexSequence = pair[A].size();
		// std::cout << "m" << "\n";
		// insertBOneToAVec(pair[B], pair[A]);
		// pair[B].erase(pair[B].begin() + 0);
		// printRes(pair, NO);
		// std::cout << "m" << "\n";
		// J = Jacobsthal(n);
		// while (pair[B].size() != 0 || b[0].position == -2)
		// {
		// 	size_t b_index;
		// 	size_t a_index;
		// 	b_index = J > maxBIndexSequence ? maxBIndexSequence : J;
		// 	a_index = J > maxAIndexSequence ? maxAIndexSequence : J;
		// 	// a jacoby routine j = 3 
		// 	//===> index in the array b for position = 3 
		// 	//==> if position 3 is not existing go to max position of b 
		// 	//==> if max == -2 that means I'm ready to push at the end of a 
		// 	//==> if max >= 0 find this position on the array a if is not existing find the max position and start binary
		// 	//==>delete
		// 	//b.size() != 0 || b[0].position == -2
		// 	while (J > Jacobsthal(n - 1))
		// 	{
		// 		std::cout << "J"<<n<<": " << J <<std::endl;
		// 		// I will go find the specific element from b by the given position take it
		// 		// b_index = (J > maxBIndexSequence) ? (maxBIndexSequence):findIndexInPairFromPosition(pair[B], J);
		// 		std::cout << "b_index: "<< b_index << std::endl;
		// 		// a_index = (J > maxAIndexSequence) ? (maxAIndexSequence):findIndexInPairFromPosition(a, J);
		// 		std::cout << "a_index: "<< a_index << std::endl;
		// 		BinarySortOne(pair[A],Jacobsthal(n - 1), a_index - 1, pair[B][b_index]);
		// 		pair[B].erase(pair[B].begin() + b_index);
		// 		J--;
		// 		maxBIndexSequence--;
		// 		maxAIndexSequence--;
		// 		printRes(pair, YES);
		// 	}
		// 	n++;
		// 	J = Jacobsthal(n);
	// 	}
	// 	size_t i = -1;
	// 	while (pair[B][++i].position != -2)
	// 		break ;
	// 	while (pair[B][i++].position == -2)
	// 	pair[A].push_back(pair[B][i]);
	// 	groups = pair[A];
	// 	// printRes(pair[A], NO);
	// }
	// //b1 a1 a2 a3 a4
	// //b2 b3 b4 b5
	// for (size_t i = 0; i != groups.size(); i++)
	// 	res.push_back(groups[i].lms[0]);
	// printRes(res, NO);
	// std::cout << std::endl;
	// return res;
// };

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