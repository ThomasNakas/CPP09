#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cctype>
class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		// helpers
		std::vector<int> fastSort(const std::vector<int>);
		//argv checker
		bool strIsNumber(const std::string&);
		bool arrOfStrAllNum(const std::string arr[], size_t size);

		bool strIsPosInt(const std::string& );
		bool arrOfPosInt(const std::string arr[], size_t size);

		// print a vector
		void printRes(const std::vector<int>);
		//print the time for vector and dque
		//template function
		template <typename Func, typename... Args>
		auto timeAFunction(Func&& func, Args&&... args, int type)
		{
			auto start = std::chrono::high_resolustion_clock::now();
			func(std::forward<Args>(args)...);
			auto end = std::chrono::high_sesolution_clock::now();
			return std::chrono::duration<double, std::micro>(end - start).count();
		}


};