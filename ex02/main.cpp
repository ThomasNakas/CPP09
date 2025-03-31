/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/31 17:33:30 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	if (pMM.inputIsValid(argv, argc) == pMM.NO)
		return 1;
	//---->Detailed Print<------------
	pMM.printBeforeAndAfter(argv, argc, pMM.YES);
	//vector implementation
	pMM.printVectorTime(argv, argc, pMM.NO);
	// //deque implementation
	pMM.printDequeTime(argv, argc, pMM.NO);
	return 0;
}
// #/bin/bash
// echo  "==============>NO INPUT:<================="
// ./PmergeMe
// echo  "========>SIMPLE INPUTS:<=================="
// ./PmergeMe  4 0 0 0 0 0 0 0 3 3 3 3 0 0 0 0 0 2 2 2 2 0 0 0 0 1 1 1 1 0 0 0 0 0 0 0 3 2 1 1 1 1 1

// ./PmergeMe 3  0 0 0 0 0 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// ./PmergeMe 4 4 4 4 3 2 1 
// ./PmergeMe 0 0 0 0 0 0 0 0 0 0 0 0 0 0
// ./PmergeMe 5 0 0 0 0 1  
// ./PmergeMe 10 10 2 1 5 4 4 4 4 7 0  
// ./PmergeMe 7 700 200 200 400 100 100 100  
// ./PmergeMe 15 1 7 7 7 9 1 0 0 0 25 25 25 2 2  
// ./PmergeMe 8 42 200 200 100  100 0 0 0 0 14 14 168  

// echo  "========>ERROR CASES:<===================="
// echo "====>Negative Input:<=============="
// echo "./PmergeMe - 0 0 0 0 0 0"
// ./PmergeMe - 0 0 0 0 0 0
// echo "=>Number to the limit 2147483647:<="
// echo "./PmergeMe 2147483647 0 0 0 0 0 0 0"
// ./PmergeMe 2147483647 0 0 0 0 0 0 0 
// echo "Number to the limit 2147483648:<==="
// echo "./PmergeMe 2147483648 0 0 0 0 0 0 0"
// ./PmergeMe 2147483648 0 0 0 0 0 0 0
// echo "=====>Negative Number:<============="
// ./PmergeMe -1 0 0 0 0 0 0 0 0 0 0 0
// echo "characters:"
// ./PmergeMe a 0 0 0 0 0 0 0 0 0 0 a 0 
// echo  "====>20 numbers:<=================="
// ./PmergeMe `jot -r 20 1 1000 | tr '\n' ' '`
// echo  "====>50 numbers:<================="
// ./PmergeMe `jot -r 50 1 1000 | tr '\n' ' '`
// echo  "====>100 numbers:<================"
// ./PmergeMe `jot -r 100 1 1000 | tr '\n' ' '`
// echo  "====>1000 numbers:<==============="
// ./PmergeMe `jot -r 1000 1 1000 | tr '\n' ' '`
// echo  "====>3000 numbers:<==============="
// ./PmergeMe `jot -r 3000 1 1000 | tr '\n' ' '`
