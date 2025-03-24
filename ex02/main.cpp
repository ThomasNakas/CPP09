/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/24 19:52:40 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	std::vector<PmergeMe::Group> groups; 
	//vector
	std::vector<int> numbers;
	std::vector<std::pair<int, int>> pairs;
	//deque
	std::deque<std::pair<int, int>> dPairs;
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

	std::cout << "Before: ";
	pMM.printRes(numbers);
	std::cout << "After:  ";
	pMM.printRes(pMM.fastSort(numbers));

	std::cout << "//==========\n";
	for (const std::pair<int, int>& p : pairs)
	{
		std::cout << "[ " << p.first;
		if (p.second != -1)
			std::cout << " " << p.second;
		else
			std::cout << " " << " ";
		std::cout <<" ] ";
	}
	std::cout << "\n//==========\n";
	return 0;
}