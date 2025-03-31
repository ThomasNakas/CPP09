/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 22:20:35 by tnakas           ###   ########.fr       */
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
	//---->Summarized Print<----------
	// pMM.printBeforeAndAfter(argv, argc, pMM.YES);
	// //vector implementation
	// pMM.printVectorTime(argv, argc, pMM.YES);
	// // //deque implementation
	// pMM.printDequeTime(argv, argc, pMM.YES);
	return 0;
}
