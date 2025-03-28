/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:54 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/28 06:07:09 by tnakas           ###   ########.fr       */
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
		int l = 0;
		int lastInsPos = -1;
		size_t readyToRemove = NO;
		enum type{A,B};
		enum print{YES, NO};
		struct Group
		{
			std::vector<int> lms;
			int repr;
			int position = -1;
			int sequence = -1;
			int size = -1;

			Group();
			Group(const std::vector<int> elems);
			Group(const Group& other);
			Group& operator=(const Group& other);
			~Group();
		};
		
		//Default Constructors
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
		void printRes(const std::vector<Group>, int details);
		void printRes(const std::vector<std::vector<Group>>, int details);
		// merge functions
		// a function that run into a vec of group
		std::vector<Group> pairMergeSorting(std::vector<Group> groups);
		void BinarySortOne(std::vector<Group>& vec, 
			int start, int end, Group element);
		void insertBOneToAVec (std::vector<Group> bSec, 
				std::vector<Group>& aSec);
		void SplitTheMergedOneLevel(std::vector<Group>& groups);
		std::vector<std::vector<PmergeMe::Group>> pairOfBAndA(std::vector<Group> gr);
		std::vector<int> sortedVectorOfGroups(std::vector<Group>& groups);
		// Helper into the logic
		int findIndexInPairFromPosition(std::vector<PmergeMe::Group> groups, int position, int seq);
		int findMaxIndex(std::vector<PmergeMe::Group> groups, int sqnc, int mx);
		int findMaxPos(std::vector<Group> groups, int sqnc);
		void protectedInsert(std::vector<Group>& vec, int start, Group element);
		void protectedPush(std::vector<Group>& vec, Group element);
		void protectedErase(std::vector<std::vector<Group>>&, int index);
		int	jacobsthalIsExisitng(std::vector<Group> gr, int jacobsthal);
	};
	int	spPow(int n1, int n2);
	int Jacobsthal(int n);
	int spMin (int a, int b);
	// I need a transition from int to sequence
	// which sequence has insice the value the position
	// in the sequence and the type of the sequence