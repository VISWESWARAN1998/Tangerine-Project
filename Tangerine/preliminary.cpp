//   SWAMI KARUPPASWAAMI THUNNAI
#include"headers.h"

bool PreliminaryTest::start_preliminary_test(double size,std::string location)
{
	std::map<double, std::string>::iterator test;
	test = preliminary_tester.find(size);
	if (test != preliminary_tester.end())
	{
		// List of files with same sizes
		std::cout << "\n Files with similar sizes have been found\n";
		preliminary_result.push_back(location);
		preliminary_result.push_back(test->second);
		std::ofstream file;
		file.open("SAME SIZED FILES.txt",std::ios::app);
		file << location << "\n";
		file << test->second << "\n";
		file.close();
	}
	else preliminary_tester[size] = location;
}

void PreliminaryTest::send_the_report_for_confirmatory_test()
{
	// Use iterators to access to the algorithms
	// I know this is lengthy but this is standard for almost all STL containers like deque, vectors etc.,
	// This method is called half open and closed iterators
	// itr = iterators which links algo to the container
	std::list<std::string>::iterator itr1 = preliminary_result.begin();
	std::list<std::string>::iterator itr2 = preliminary_result.end();
	for (std::list<std::string>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::cout << "\nSending the result for confirmatory test...\n";
		preliminary_test_result.push_back(*itr);
		std::cout << *itr;
	}
	std::list<std::string>::iterator itr3 = preliminary_test_result.begin();
	std::list<std::string>::iterator itr4 = preliminary_test_result.end();
	for (std::list<std::string>::iterator itr = itr3; itr != itr4; ++itr)
	{
		std::cout << "\nProcessing confirmatory test...\n";
		std::cout << *itr;
		confirm(*itr);
	}
}