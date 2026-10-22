#pragma once
#include "../src/Schedule.h"
#include "../src/Task2.h"
#include "stdexcept"

std::vector<record> greedy_schedule(Schedule& s);

namespace greedy {

	int calculate_penalty(const std::vector<record>& records, Schedule& s);
	void printOutput(const std::vector<record>& records, Schedule& s);

}