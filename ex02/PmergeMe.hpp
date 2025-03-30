/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:54 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/30 16:07:03 by tnakas           ###   ########.fr       */
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
		int minIns = 2147483647;
		enum type{A,B};
		enum print{YES, NO};
		struct Group
		{
			std::vector<int> lms;
			std::deque<int> lmsD;
			int repr;
			int size;
			int position;
			int sequence;

			Group();
			//-------template alternative------
			Group(const std::vector<int>& elems);
			Group(const std::deque<int>& elemsD);
			Group(const Group& other);
			Group& operator=(const Group& other);
			~Group();
		};
		
		//=======Default Constructors===============================================================
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		//=======argv checker=======================================================================
		bool IsNbr(const std::string&);
		bool IsPInt(const std::string& );
		//========Input Validation==================================================================
		int inputIsValid (char* argv[], int argc);
		//=======the primary functions==============================================================
		std::vector<int> primaryVec(char* argv[], int argc);
		std::deque<int> primaryDeq(char* argv[], int argc);
		//=======trial helpers======================================================================
		std::vector<int> fastSort(const std::vector<int>);
		std::deque<int> fastSort(const std::deque<int>);
		
		//=======print a vector=====================================================================
		void printRes(const std::vector<int>);
		void printRes(const std::vector<Group>, int details);
		void printRes(const std::vector<std::vector<Group>>, int details);
		//=======print a deque
		void printRes(const std::deque<int> dq);
		void printRes(const std::deque<Group>, int details);
		void printRes(const std::deque<std::deque<Group>>, int details);
		//=======Soritng less than three============================================================
		//----->vectors<-------
		int SortingLessThanThree (std::vector<Group>& vec);
		//----->deques<--------
		int SortingLessThanThree (std::deque<Group>& dq);
		//=======Pair merge sorting=================================================================
		//----->vectors<-------
		std::vector<Group> pairMergeSorting(std::vector<Group> groups);
		//----->deques<--------
		std::deque<Group> pairMergeSorting(std::deque<Group> groups);
		//=======Binary Sorting One=================================================================
		//----->vectors<-------
		void BinarySortOne(std::vector<Group>& vec, int start, int end, Group element);
		//----->deques<--------
		void BinarySortOne(std::deque<Group>& dq, int start, int end, Group element);
		//=======Insert b1 to A sequence============================================================
		//----->vectors<-------
		void insertBOneToAVec (std::vector<Group> bSec, std::vector<Group>& aSec);
		//----->deques<--------
		void insertBOneToAVec (std::deque<Group> bSecD, std::deque<Group>& aSecD);
		//=======Split the merged one level=========================================================
		//----->vectors<-------
		void SplitTheMergedOneLevel(std::vector<Group>& groups);
		//----->deques<--------
		void SplitTheMergedOneLevel(std::deque<Group>& groups);
		//=======creating the pair sequences========================================================
		//----->vectors<-------
		std::vector<std::vector<PmergeMe::Group>> pairOfBAndA(std::vector<Group> gr);
		//----->deques<--------
		std::deque<std::deque<PmergeMe::Group>> pairOfBAndA(std::deque<Group> gr);
		//=======Jabosthal index searching -->binary sorting --> until level 0======================
		//----->vectors<-------
		std::vector<int> sortedVectorOfGroups(std::vector<Group>& groups);
		//----->deques<--------
		std::deque<int> sortedDequeOfGroups(std::deque<Group>& groups);
		//=======Helper into the logic==============================================================
		//----->vectors<-------
		int findIndexInPairFromPosition(std::vector<PmergeMe::Group> groups, int position, int seq);
		int findMaxIndex(std::vector<PmergeMe::Group> groups, int sqnc, int mx);
		int findMaxPos(std::vector<Group> groups, int sqnc);
		void protectedInsert(std::vector<Group>& vec, int start, Group element);
		void protectedPush(std::vector<Group>& vec, Group element);
		void protectedErase(std::vector<std::vector<Group>>&, int index);
		int	jacobsthalIsExisitng(std::vector<Group> gr, int jacobsthal);
		//----->deques<--------
		int findIndexInPairFromPosition(std::deque<PmergeMe::Group> groups, int position, int seq);
		int findMaxIndex(std::deque<PmergeMe::Group> groups, int sqnc, int mx);
		int findMaxPos(std::deque<Group> groups, int sqnc);
		void protectedInsert(std::deque<Group>& vec, int start, Group element);
		void protectedPush(std::deque<Group>& vec, Group element);
		void protectedErase(std::deque<std::deque<Group>>&, int index);
		int	jacobsthalIsExisitng(std::deque<Group> gr, int jacobsthal);
	};
	int	spPow(int n1, int n2);
	int Jacobsthal(int n);
	int spMin (int a, int b);
	// I need a transition from int to sequence
	// which sequence has insice the value the position
	// in the sequence and the type of the sequence