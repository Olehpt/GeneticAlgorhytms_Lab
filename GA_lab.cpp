#include "GA_lab.h"
#include <gapp/gapp.hpp>
#include "src/Task1.h"
#include "src/Task2.h"
#include "other/Gradient.h"
#include "other/GreedySchedule.h"

void main()
{
	Schedule s(data);
	task2_solve();

	auto r = greedy_schedule(s);
	std::cout << "\n\ngreedy schedule:\n\n";
	greedy::printOutput(r, s);
	return;
}
