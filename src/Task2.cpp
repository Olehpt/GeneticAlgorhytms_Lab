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
        T2{ s },
        gapp::Bounds{
            gapp::IntegerGene{0},
            static_cast<gapp::IntegerGene>(maxGene)
        }
    );

    const auto& best = solutions.front().chromosome;

    std::vector<int> chromosome(best.begin(), best.end());
    //output preparations

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

std::string roomTypeConvert(int id) {
    roomType rt = rooms[id].type;
    if (rt == roomType::Computer) return "Computer";
    else if (rt == roomType::Lecture) return "Lecture";
    else if (rt == roomType::Regular) return "Practice";
    else return "unknown";
}

void printOutput(std::vector<std::vector<std::vector<geneOutput>>>& table)
{
    //output1
    for (size_t d = 0; d < table.size(); ++d) {
        std::cout << "Day " << d + 1 << '\n';

        for (size_t t = 0; t < table[d].size(); ++t) {
            if (table[d][t].empty())
                continue;

            std::cout << "  Slot " << t + 1 << '\n';

            for (const auto& o : table[d][t]) {
                std::cout << "      ";
                std::cout << groups[o.l.group_id] << "; " << subjects[o.l.subject_id] << "; " << rooms[o.r.room_id].name << "; " << roomTypeConvert(o.r.room_id) << "; " << teachers[o.l.teacher_id]
                    << "\n";
            }
        }
    }
}

void printOutputAsArray(std::vector<std::vector<std::vector<geneOutput>>>& table)
{
    //output2
    std::cout << "\n\n array view: \n\n";
    for (size_t d = 0; d < table.size(); ++d) {
        std::cout << "Day " << d + 1 << '\n';

        for (size_t t = 0; t < table[d].size(); ++t) {
            if (table[d][t].empty())
                continue;

            std::cout << "  Slot " << t + 1 << '\n';

            for (const auto& o : table[d][t]) {
                std::cout << "      ";
                std::cout << o.l.group_id << "; " << o.l.teacher_id << "; " << o.l.subject_id << "; " << roomTypeConvert(o.r.room_id) << "; " << o.r.room_id
                    << "\n";
            }
        }
    }
}

