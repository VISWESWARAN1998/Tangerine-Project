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
/*
Fixture of the small bug:
Initial implementation was something like this
when a file is not present in the map it is added else it is added into the list
so only one duplicate files is removed
The bug has been solved - below is the explanation:
confirmatory_result consits of all duplicate files including the file which is not to be deleted
That has been filtered using map and conditional statements
*/

void ConfirmatoryTest::process_duplicates()
{
	std::list<std::string>::iterator itr1 = confirmatory_result.begin();
	std::list<std::string>::iterator itr2 = confirmatory_result.end();
	int count = 0;	
	
	for (std::list<std::string>::iterator itr = itr1; itr != itr2; ++itr)
	{
		std::string proc = get_hash_for(*itr);
		bool can_add = true;
		std::map<std::string, std::string>::iterator clean = remove_duplicates.find(proc);
		if (clean == remove_duplicates.end())
		{
			remove_duplicates[proc] = *itr;
		}
		else
		{
			std::list<std::string>::iterator check_addition1 = remove_these_files.begin();
			std::list<std::string>::iterator check_addition2 = remove_these_files.end();
			std::map<std::string, std::string>::iterator find1 = remove_duplicates.begin();
			std::map<std::string, std::string>::iterator find2 = remove_duplicates.end();
			for (std::list<std::string>::iterator check_addition = check_addition1; check_addition != check_addition2; ++check_addition)
			{
				for (std::map<std::string, std::string>::iterator find = find1; find != find2; ++find)
				{
					if (find->second == *itr)can_add = false;
				}
			}
			if(can_add==true)remove_these_files.push_back(*itr);
		}
		count++;
	}
	std::cout << "\n" << count << "  Files will be processed continue [y/n]: ";
	char input;
	std::cin >> input;
	if (input == 'y')
	{
		std::list<std::string>::iterator top = remove_these_files.begin();
		std::list<std::string>::iterator bottom = remove_these_files.end();
		std::cout << "\n These are the files to be removed\n";
		for (std::list<std::string>::iterator accesses = top; accesses != bottom; ++accesses)
		{
			std::cout <<*accesses<<"\n";
		}
		std::cout << "\n Press any alphabetical/numerical key to continue or close the window to terminate the process\n";
		std::cin >> input;
		for (std::list<std::string>::iterator accesses = top; accesses != bottom; ++accesses)
		{
			if (std::ifstream(*accesses))
			{
				std::cout << "\nRemoving:" << *accesses;
				std::string rem = *accesses;
				remove(rem.c_str());
				std::cout << "\nRemoved:" << *accesses;
			}

		}
	}
}