// SWAMI KARUPPASWAMI THUNNAI
#pragma once

#include"headers.h"


class PreliminaryTest:public ConfirmatoryTest
{
private:
	// This map is used to identify files with same sizes
	std::map<double, std::string> preliminary_tester;
	// This list will contain the files with same sizes
	std::list<std::string> preliminary_result;
public:
	bool start_preliminary_test(double size,std::string location);
	void send_the_report_for_confirmatory_test();
};