#include "Task2.h"
#include <iostream>
#include "ScheduleOutput.h"
#include <fstream>

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

void task2_metric(int p, double c, double m, int generations, const std::string& fileoutput) {
    _Schedule data = { lessons, rooms, groups, subjects, teachers };
    Schedule s(data);

    const int maxGene = s.days * s.timeslots * static_cast<int>(rooms.size()) - 1;

    gapp::IntegerGA ga(
        p,
        gapp::crossover::integer::TwoPoint{ c },
        gapp::mutation::integer::Uniform{ m }
    );

    ga.track(
        gapp::metrics::FitnessMax{},
        gapp::metrics::FitnessMean{}
    );

    auto solutions = ga.solve(
        T2{ s },
        gapp::Bounds{
            gapp::IntegerGene{0},
            static_cast<gapp::IntegerGene>(maxGene)
        },
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

