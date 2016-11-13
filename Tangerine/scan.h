#pragma once

#include<iostream>
#include<string>
#include<map>
#include<list>
#include<map>
#include<list>
#include"preliminary.h"

// Processing the files



class Process:public PreliminaryTest
{
public:
	bool scan(std::string location);
	double getSize(std::string location);
};


