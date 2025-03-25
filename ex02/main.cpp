/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/25 17:07:29 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	std::vector<PmergeMe::Group> groups; 
	//vector
	std::vector<int> numbers;
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
	//-----
	for (size_t i = 0; i < numbers.size(); i++)
		groups.emplace_back(std::vector<int>{numbers[i]});
	// if (numbers.size() % 2 != 0)
	// 	groups.emplace_back(std::vector<int>{numbers.back()});
	std::vector<PmergeMe::Group> sortedGroups = pMM.pairMergeSorting(groups);
	// std::cout << "main print" << std::endl;

	pMM.printRes(sortedGroups);
	PmergeMe::Group g;
	g.lms = {2, 14};
	pMM.BinarySortOne(sortedGroups, 0, sortedGroups.size() - 1, g),
	std::cout << "main print" << std::endl;
	pMM.printRes(sortedGroups);
	// pMM.SplitTheMergedOneLevel(sortedGroups);
	pMM.printRes(sortedGroups);
	BinarySortOne(numbers, 0, numbers.size() - 1, 14);
	pMM.printRes(numbers);
	std::cout << std::endl;
	std::cout << "Before: ";
	pMM.printRes(numbers);
	std::cout << std::endl;
	std::cout << "After:  ";
	pMM.printRes(pMM.fastSort(numbers));
	std::cout << std::endl;

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