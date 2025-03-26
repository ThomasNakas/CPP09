/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/26 15:14:29 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	std::vector<PmergeMe::Group> groups;
	std::vector<std::vector<PmergeMe::Group>> pair;
	//vector
	std::vector<int> numbers;
	std::vector<int> res;
	//deque
	if (argc < 2)
	{
		std::cerr << "Error: No input provided.\n";
		return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		if (!pMM.IsNbr(argv[i]) || !pMM.IsPInt(argv[i]))
		{
			std::cerr 
			<< "Error: arguments needs to be possitive or equal with zero integers\n";
			return 1;
		}
	}
	//make the argv a vector
	//----- form argv[1] until argc - 1
	for (int i = 1; i < argc; i++)
		numbers.push_back(std::stoi(argv[i]));
	if (numbers.size() == 3)
		for (size_t i = 0; i + 1 != numbers.size(); i++)
			for (size_t j = i; j != numbers.size(); j++)
				if (numbers[i] > numbers[j])
					std::swap(numbers[i], numbers[j]);
	//-----
	for (size_t i =0; i + 1 < numbers.size(); i+=2)
		if (numbers[i] > numbers[i + 1])
			std::swap(numbers[i], numbers[i + 1]);
	for (size_t i = 0; i < numbers.size(); i++)
		groups.emplace_back(std::vector<int>{numbers[i]});
	std::cout << "size of primary network: " << numbers.size() << std::endl;
	// std::vector<PmergeMe::Group> sortedGroups = pMM.pairMergeSorting(groups);
	std::cout << "main print" << std::endl;
	pMM.printRes(groups, pMM.NO);
	std::cout << "size of primary network: " << groups.size() << std::endl;
	std::cout << "main print" << std::endl;
	// res = pMM.sortedVectorOfGroups(sortedGroups);
	// PmergeMe::Group g;
	// g.lms = {2, 14};
	// pMM.BinarySortOne(sortedGroups, 0, sortedGroups.size() - 1, g),
	// std::cout << "main print" << std::endl;
	// pMM.printRes(sortedGroups, pMM.YES);
	// std::cout << "level: "<< pMM.l << std::endl;
	// pMM.SplitTheMergedOneLevel(sortedGroups);
	// pMM.printRes(sortedGroups, pMM.YES);
	// pair = pMM.pairOfBAndA(sortedGroups);
	// pMM.printRes(pair, pMM.YES);
	// pMM.insertBOneToAVec(pair[pMM.B], pair[pMM.A]);
	// pMM.printRes(pair, pMM.YES);
	res = pMM.sortedVectorOfGroups(groups);
	// pair = pMM.pairOfBAndA(sortedGroups);
	// pMM.printRes(pair);
	// BinarySortOne(numbers, 0, numbers.size() - 1, 14);
	// pMM.printRes(numbers);
	// std::cout << std::endl;
	// std::cout << "Before: ";
	// pMM.printRes(numbers);
	// std::cout << std::endl;
	// std::cout << "After:  ";
	// pMM.printRes(pMM.fastSort(res));
	// std::cout << std::endl;

	// std::cout << "//==========\n";
	// BinarySortOne(numbers, 0, numbers.size() - 1, 9);
	// pMM.printRes(numbers);
	// std::cout << "\n//==========\n";
	// by taking two vectors to take the first element and insert it to the second one
	return 0;
}

// to split according to the reccursion level
// as input can have a vector of group
// is going to every element is checking if the element.size() == sPow(2, level)
// I need a1 b1 b2 b3 .....
// if position is j
// sorted vector of groups 
// a1 b1 b2 b3 . . .
// how I can find the position ?
// serial search on the position (same position different sequence)
// απο jacobsthal binary (Jn-1 Jn - 1)  δηλαδη σε όλη αυτήν την πραγματική διαφορά
// both of the vectors are dynamic
