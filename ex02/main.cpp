/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 01:50:33 by tnakas           ###   ########.fr       */
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
			<< "Error: arguments needs to be possitive (or equal with zero) integers\n";
			return 1;
		}
	}
	//vector implementation
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
	res = pMM.sortedVectorOfGroups(groups);
	//deque implementation
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
