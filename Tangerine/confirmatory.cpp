// SWAMI KARUPPASWAMI THUNNAI

#include"md5.h"
#include "headers.h"


std::string ConfirmatoryTest::get_hash_for(const std::string location)
{
	// I know this the below line may be omitted but it adds clarity
	std::string current_location = location;
	char* processed_location = new char[current_location.length() + 1];
	strcpy(processed_location, location.c_str());
	std::cout << "\n\n\n===>" << location;
	std::string md5;
	md5 = CALL_MD5_Function(processed_location);
	delete[] processed_location; // it is important to free up the memory
	return md5;
}

void ConfirmatoryTest::confirm(std::string location)
{
	std::string current_hash;
	current_hash = get_hash_for(location);
	std::map<std::string, std::string>::iterator test;
	test = confirmatory_tester.find(current_hash);
	if (test != confirmatory_tester.end())
	{
		confirmatory_result.push_back(location);
		confirmatory_result.push_back(test->second);
		// Some logging will help to identify the problem
		std::ofstream file;
		file.open("DUPLICATES.txt", std::ios::app);
		file << location << "\n";
		file << test->second << "\n";
		file.close();
	}
	else
	{
		// This will save the current hash and locations
		confirmatory_tester[current_hash] = location;
	}
}
