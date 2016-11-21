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
		int input1;
		std::cout << "\n Press 1 to remove all files or 2 to remove selective files\n";
		std::cin >> input1;
		int id = 0; //This denotes the id of the files
		switch (input1)
		{
		case 1:
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
			break;
		case 2: 
			
			for (std::list<std::string>::iterator accesses1 = top; accesses1 != bottom; ++accesses1)
			{
				if (std::ifstream(*accesses1)) //location check is necessary
				{
					std::cout << *accesses1 << " checker runnig\n";
					std::string real = *accesses1;
					remove_selected[id] = real;
					id++; // Id gets incremented so that we can get unique address
				}
			}
			for (int i = 0; i < 10; i++)std::cout << "\n"; // we need space
			std::cout << "The files to be removed\n========================================\n";
			for (std::map<int, std::string>::iterator selective_removal = remove_selected.begin(); selective_removal != remove_selected.end(); ++selective_removal)
			{
				std::cout<< selective_removal->first<<"=>   "<<selective_removal->second << "\n";
			}
			while (1)
			{
				int no; // id
				std::cout << "Enter the no displayed in the screen to remove the file\n";
				std::cin >> no;
				std::map<int, std::string>::iterator search_for_id;
				search_for_id = remove_selected.find(no);
				if (search_for_id != remove_selected.end())
				{
					if (std::ifstream(search_for_id->second))remove(search_for_id->second.c_str());
					else std::cout << "\nFile has been removed already";
				}
				else std::cout << "\nInvalid ID try again\n";
			}
			break;
		default:
			std::cout << "\nAbort";
		}
	}
}