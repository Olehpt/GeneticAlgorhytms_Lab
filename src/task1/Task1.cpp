#include "Task1.h"
#include <fstream>

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

void task1_metric(int p, double c, double m, int generations, const std::string& fileoutput)
{
	gapp::RCGA ga(
		p,
		gapp::crossover::real::Arithmetic{ c },
		gapp::mutation::real::Uniform{ m }
	);

	ga.track(
		gapp::metrics::FitnessMax{},
		gapp::metrics::FitnessMean{}
	);

	auto solutions = ga.solve(
		T1{},
		gapp::Bounds{ -5.0, 5.0 },
		generations
	);

	auto bestFitness =
		ga.get_metric<gapp::metrics::FitnessMax>();

	auto meanFitness =
		ga.get_metric<gapp::metrics::FitnessMean>();

	std::ofstream file(fileoutput);

	if (!file.is_open()) {
		std::cerr << "Failed to open output file\n";
		return;
	}

	file << "Generation,BestPenalty,MeanPenalty\n";

	for (size_t i = 0; i < bestFitness.size(); ++i) {
		double bestPenalty = -bestFitness[i][0];
		double meanPenalty = -meanFitness[i][0];

		file << i << ','
			<< bestPenalty << ','
			<< meanPenalty << '\n';
	}
}
