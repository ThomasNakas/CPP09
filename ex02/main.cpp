#include "PmergeMe.hpp"


int main(int argc, char* argv[])
{
	PmergeMe sorting;
	std::vector<int> numbers;
	if (argc < 2)
	{
		std::cerr << "Error: No input provided.\n";
		return 1;
	}
	std::string args[argc - 1];
	for (int i = 1; i < argc; i++)
		args[i - 1] = argv[i];

	std::vector<int> numbers;
	if (!sorting.arrOfStrAllNum(args , argc))
	{
		std::cerr << "Error: Arguments must be numbers only.\n";
		return 1;
	}
	if (!sorting.arrOfPosInt(args , argc))
	{
		std::cerr << "Error: Arguments must be positive integers only.\n";
		return 1;
	}
	for (std::string str : args)
		numbers.push_back(std::stoi(str));
	std::cout << "Before: ";
	sorting.printRes(numbers);
	std::cout << "After: ";
	sorting.printRes(sorting.fastSort(numbers));
	//print for vector
	std::deque<int> deq(numbers.begin(), numbers.end());
	std::cout << "Time to process a range of " << numbers.size()
				<< " elements with std::vector: " << sorting.timeAFunction(sorting.mergeInSort, numbers);
	// print for dque
	std::cout << "Time to process a range of " << numbers.size()
				<< " elements with std::deque: " <<	sorting.timeAFunction(sorting.mergeInSort, deq);
	return 0;
}