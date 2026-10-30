#include "Task2.h"
#include <iostream>
#include "ScheduleOutput.h"

gapp::FitnessVector T2::invoke(
    const gapp::Candidate<gapp::IntegerGene>& c) const {
    std::vector<int> chromosome(
        c.chromosome.begin(),
        c.chromosome.end()
    );

    int penalty = calculate_penalty(chromosome, s);

    return { -static_cast<double>(penalty) };
}

void task2_solve(int p, double c, double m, int generations) {
    const int populationSize = p;
    const double crossoverRate = c;
    const double mutationRate = m;

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
        T2{ s },
        gapp::Bounds{
            gapp::IntegerGene{0},
            static_cast<gapp::IntegerGene>(maxGene)
        },
        generations
    );

    const auto& best = solutions.front().chromosome;

    std::vector<int> chromosome(best.begin(), best.end());
    
    //output

    std::cout << "Besh schedule:\n";

    std::vector<geneOutput> outputs = {};
    for (size_t i = 0; i < chromosome.size(); ++i) {
        outputs.push_back(geneOutput(s.decode(chromosome[i]), s.data.lessons[i]));
    }
    std::vector<std::vector<std::vector<geneOutput>>> table(s.days, std::vector<std::vector<geneOutput>>(s.timeslots));
    for (const auto& o : outputs) {
        table[o.r.day][o.r.timeslot].push_back(o);
    }
    
    printOutput(table);
    //printOutputAsArray(table);

    std::cout << "\nTotal penalty: " << calculate_penalty(chromosome, s) << '\n';
}

