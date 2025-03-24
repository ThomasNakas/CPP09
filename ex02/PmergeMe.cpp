#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

};
PmergeMe::~PmergeMe()
{
};
PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
};

void PmergeMe::printRes(const std::vector<int> vec)
{
	for(int n : vec)
		std::cout << n << " ";
	std::cout << std::endl;
}

bool PmergeMe::strIsNumber(const std::string& str)
{
	return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool PmergeMe::arrOfStrAllNum(const std::string arr[], size_t size)
{
	return std::all_of(arr, arr + size,
		 [this](const std::string& s)
		{
			return this->strIsNumber(s);
		});
};

bool PmergeMe::strIsPosInt(const std::string& str)
{
	return  (
				std::stod(str) >= 0.0 
				|| std::stod(str) <= 2147483647.0
			);
};
bool PmergeMe::arrOfPosInt(const std::string arr[], size_t size)
{
	return std::all_of(arr, arr + size,
		[this](const std::string& s)
		{return this->strIsPosInt(s);});
};

std::vector<int> PmergeMe::fastSort(const std::vector<int> numbers)
{
	std::vector<int> temp = numbers;
	for(unsigned int n = 0; n != temp.size() - 1; n++)
		for (unsigned int m = n + 1; m != temp.size(); m++)
			if (numbers[n] > numbers[m])
				std::swap(temp[n], temp[m]);
	return temp;
}