#include "Task2.h"
#include <iostream>

gapp::FitnessVector T2::invoke(
    const gapp::Candidate<gapp::IntegerGene>& c) const {
    std::vector<int> chromosome(
        c.chromosome.begin(),
        c.chromosome.end()
    );

    int penalty = calculate_penalty(chromosome, s);

    return { -static_cast<double>(penalty) };
}

void task2_solve() {
    const int populationSize = 100;
    const double crossoverRate = 0.8;
    const double mutationRate = 0.1;

    _Schedule data = { lessons, rooms, groups, subjects, teachers };
    Schedule s(data);

    const int maxGene =
        s.days * s.timeslots * static_cast<int>(rooms.size()) - 1;

    gapp::IntegerGA ga(
        populationSize,
        gapp::crossover::integer::TwoPoint{ crossoverRate },
        gapp::mutation::integer::Uniform{ mutationRate }
    );

    auto solutions = ga.solve(
        T2{s},
        gapp::Bounds{
            gapp::IntegerGene{0},
            static_cast<gapp::IntegerGene>(maxGene)
        }
    );

    const auto& best = solutions.front().chromosome;

    std::vector<int> chromosome(best.begin(), best.end());
}