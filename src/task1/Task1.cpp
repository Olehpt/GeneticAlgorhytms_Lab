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

void task1_solve(int p, double c, double m, int generations) {
	const int populationSize = p;
	const double crossoverRate = c;
	const double mutationRate = m;

	gapp::RCGA ga(
		populationSize,
		gapp::crossover::real::Arithmetic{ crossoverRate },
		gapp::mutation::real::Uniform{ mutationRate }
	);

	auto solutions = ga.solve(
		T1{},
		gapp::Bounds{ -5.0, 5.0 },
		generations
	);

	const auto& best = solutions.front().chromosome;

	std::cout << "Best solution:\nx = " << best[0] << ", y = " << best[1] << "\n" << "f = " << func(best[0], best[1]) << "\n";
}