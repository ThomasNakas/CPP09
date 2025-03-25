/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:54 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/25 17:07:41 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <utility>
#include <cmath>
class PmergeMe
{
	public:
		size_t l = 0;
		struct Group
		{
			std::vector<int> lms;
			int repr;

			Group();
			Group(const std::vector<int> elems);
			Group(const Group& other);
			Group& operator=(const Group& other);
			~Group();
		};
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		// helpers
		std::vector<int> fastSort(const std::vector<int>);
		//argv checker
		bool IsNbr(const std::string&);
		bool IsPInt(const std::string& );
		
		// print a vector
		void printRes(const std::vector<int>);
		void printRes(const std::vector<Group>);
		// merge functions
		// a function that run into a vec of group
		std::vector<Group> pairMergeSorting(std::vector<Group> groups);
		void BinarySortOne(std::vector<Group>& vec, 
			int start, int end, Group element);
		void insertBOneToAVec (const std::vector<Group> bSec, 
				std::vector<Group>& aSec);
		void SplitTheMergedOneLevel(std::vector<Group>& groups);
	};
	int	spPow(int n1, int n2);
	int jSeq(int n);
	void BinarySortOne(std::vector<int>& vec, 
		int start, int end, int element);
	void insertBOneToAVec (const std::vector<int> bSec, 
		std::vector<int>& aSec);