// SWAMI KARUPPASWAMI THUNNAI
// Tangerine.cpp : Defines the entry point for the console application.
// Programmed by VISWESWARAN N (C), 2016


#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include"scan.h"






int main()
{
	std::cout << "Tangerine Solutions\n";
	std::string location;
	std::cout << "Enter the location :" << std::endl;
	getline(std::cin, location);
	Process process;
	process.scan(location);
	int stay;
	std::cin >> stay;
	return 0;
}

