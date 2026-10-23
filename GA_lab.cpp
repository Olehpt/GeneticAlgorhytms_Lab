#include "GA_lab.h"
#include <gapp/gapp.hpp>
#include "src/Task1.h"
#include "src/Task2.h"
#include "other/Gradient.h"
#include "other/GreedySchedule.h"

#include <chrono>

template <typename F, typename... Args>
double t(F&& function, Args&&... args)
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
	
	return;
}



