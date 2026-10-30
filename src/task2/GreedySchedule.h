#pragma once
#include "Schedule.h"
#include "Task2.h"
#include <stdexcept>
#include "ScheduleOutput.h"

std::vector<record> greedy_schedule(Schedule& s);

namespace greedy {

	int calculate_penalty(const std::vector<record>& records, Schedule& s);
	void printOutput(const std::vector<record>& records, Schedule& s);

}