#include "Task2.h"
#include <iostream>

gapp::FitnessVector T2::invoke(
    const gapp::Candidate<gapp::IntegerGene>& c) const {
    std::vector<int> chromosome(
        c.chromosome.begin(),
        c.chromosome.end()
    );

    int penalty = calculate_penalty(chromosome, lessons);

    return { -static_cast<double>(penalty) };
}

void task2_solve() {
    const int populationSize = 100;
    const double crossoverRate = 0.8;
    const double mutationRate = 0.1;

    const int maxGene =
        DAYS * TIMESLOTS * static_cast<int>(rooms.size()) - 1;

    gapp::IntegerGA ga(
        populationSize,
        gapp::crossover::integer::TwoPoint{ crossoverRate },
        gapp::mutation::integer::Uniform{ mutationRate }
    );

    auto solutions = ga.solve(
        T2{},
        gapp::Bounds{
            gapp::IntegerGene{0},
            static_cast<gapp::IntegerGene>(maxGene)
        }
    );

    const auto& best = solutions.front().chromosome;

    std::vector<int> chromosome(best.begin(), best.end());

    std::cout << "Best penalty: "
        << calculate_penalty(chromosome, lessons)
        << "\n\n";

    for (size_t i = 0; i < chromosome.size(); ++i) {
        record r = decode(chromosome[i]);
		lesson l = lessons[i];
        std::cout << "Lesson | group= " << l.group
            << ": day=" << r.day
            << ", timeslot=" << r.timeslot
            << ", room=" << rooms[r.roomid].id
            << '\n';
    }
}