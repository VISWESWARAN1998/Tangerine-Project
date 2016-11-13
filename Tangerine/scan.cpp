#include<iostream>
#include<conio.h>
#include<fstream>
#include<Windows.h>
#include<boost\filesystem.hpp>
#include"scan.h"
namespace v = boost::filesystem;
bool Process::scan(std::string location)
{
	for (v::recursive_directory_iterator end, file(location); file != end; ++file)
	{
		if (file->status().type() != v::regular_file) std::cout << "|| System file has been found skipping\n";
		else
		{
			std::string loc = file->path().string(); // We will get the location
			std::cout << "|| Processing " << loc << "\n";
			std::cout << "|| SIZE: " << getSize(loc) << "\n";
			std::cout << "|| Performing the preliminary test...\n";
			double size_of_current_file = getSize(loc);
			start_preliminary_test(size_of_current_file, loc);
		}
	}
	send_the_report_for_confirmatory_test();
	return true;
}

double Process::getSize(std::string location)
{
	std::ifstream in;
	in.open(location, std::ifstream::ate | std::ifstream::binary);
	double size = in.tellg();
	return size;
}




