/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:52:54 by tnakas            #+#    #+#             */
/*   Updated: 2025/03/25 10:57:08 by tnakas           ###   ########.fr       */
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
			size_t level = 0;
			std::vector<int> elements;
			int representator;

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
		int	spPow(int n1, int n2);
		//argv checker
		bool IsNbr(const std::string&);
		bool IsPInt(const std::string& );

		// print a vector
		void printRes(const std::vector<int>);
		void printRes(const std::vector<Group>);
		std::vector<Group> mergeGroups(std::vector<Group> groups);
};