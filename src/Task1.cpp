#include "Task1.h"

double func(double x, double y) {
	double f = abs(x) + abs(y) + 3 * (1 - cos(4 * x)) + 3 * (1 - cos(4 * y));
	return f;
}

gapp::FitnessVector T1::invoke(const gapp::Candidate<gapp::RealGene>& c) const {
	double x = c[0];
	double y = c[1];
	return { -1 * func(x, y) };
}

void task1_solve() {
	const int populationSize = 100;
	const double crossoverRate = 0.8;
	const double mutationRate = 0.1;

	gapp::RCGA ga(
		populationSize,
		gapp::crossover::real::Arithmetic{ crossoverRate },
		gapp::mutation::real::Uniform{ mutationRate }
	);

	auto solutions = ga.solve(
		T1{},
		gapp::Bounds{ -5.0, 5.0 }
	);

	const auto& best = solutions.front().chromosome;

	std::cout << "Best solution: x = " << best[0] << ", y = " << best[1] << std::endl;
}