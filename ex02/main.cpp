/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 17:28:48 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	//vector
	std::vector<int> res;
	//deque
	std::deque<int> resD;
	if (pMM.inputIsValid(argv, argc) == pMM.NO)
		return 1;
	//vector implementation
	std::cout << "Before Vector:\n";
	pMM.printRes(res);
	std::cout << "\n";
	auto startVec = std::chrono::high_resolution_clock::now();
	res = pMM.primaryVec(argv, argc);
	auto endVec = std::chrono::high_resolution_clock::now();
	auto durationVec = std::chrono::duration_cast<std::chrono::microseconds>(endVec - startVec); //I need to add a count at the end when I'm printing
	std::cout << "After Vector:\n";
	pMM.printRes(res);
	std::cout << "\n";
	std::cout << "Before Deque:\n";
	pMM.printRes(resD);
	std::cout << "\n";
	auto startDeque = std::chrono::high_resolution_clock::now();
	resD = pMM.primaryDeq(argv, argc);
	auto endDeque = std::chrono::high_resolution_clock::now();
	auto durationDeque = std::chrono::duration_cast<std::chrono::microseconds>(endDeque - startDeque); // I need to use the count() at the end
	std::cout << "After Deque:\n";
	pMM.printRes(resD);
	std::cout << "\n";
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
