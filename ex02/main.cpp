/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 05:46:17 by tnakas           ###   ########.fr       */
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
	res = pMM.primaryVec(argv, argc);
	std::cout << "After Vector:\n";
	pMM.printRes(res);
	std::cout << "\n";
	std::cout << "Before Deque:\n";
	pMM.printRes(resD);
	std::cout << "\n";
	resD = pMM.primaryDeq(argv, argc);
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
