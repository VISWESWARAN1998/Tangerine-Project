// SWAMI KARUPPASWAMI THUNNAI
#pragma once
#include"headers.h"


class ConfirmatoryTest
{
private:
	// Map to identify the hash matching
	std::map<std::string, std::string> confirmatory_tester;
	

// The Member of This access specifier is used between member function of different class - so no provate
protected:
	std::list<std::string> preliminary_test_result;
	// We have to remove the files actullay
	std::map<std::string, std::string> remove_duplicates;
	// Final Neat and Clean list of the locations of duplicate files are been stored here
	std::list<std::string> confirmatory_result;
	// Scheduled removal process
	std::list<std::string> remove_these_files;
public:
	std::string get_hash_for(const std::string location);
	void confirm(std::string location);
	void process_duplicates();
};
