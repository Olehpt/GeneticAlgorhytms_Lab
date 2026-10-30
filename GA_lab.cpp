#include "GA_lab.h"
#include <gapp/gapp.hpp>
#include "src/task1/Task1.h"
#include "src/task1/Gradient.h"
#include "src/task2/Task2.h"
#include "src/task2/GreedySchedule.h"

#include <chrono>

template <typename F, typename... Args>
double get_time(F&& function, Args&&... args)
{
	auto start = std::chrono::steady_clock::now();
	std::invoke(
		std::forward<F>(function),
		std::forward<Args>(args)...
	);
	auto end = std::chrono::steady_clock::now();
	return std::chrono::duration<double>(end - start).count();
}

void main()
{
	Schedule s(data);
	
	task2_solve(100, 0.8, 0.1, 50);

	return;
}