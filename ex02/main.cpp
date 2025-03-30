/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:39 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 19:16:07 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe pMM;
	if (pMM.inputIsValid(argv, argc) == pMM.NO)
		return 1;
	pMM.printBeforeAndAfter(argv, argc);
	//vector implementation
	pMM.printVectorTime(argv, argc);
	// //deque implementation
	pMM.printDequeTime(argv, argc);
	return 0;
}
