#include "GreedySchedule.h"


std::vector<record> greedy_schedule(Schedule& s) {
    std::vector<record> result;
    result.reserve(s.data.lessons.size());

    if (s.data.rooms.empty())
        throw std::invalid_argument("No rooms");

    for (size_t i = 0; i < s.data.lessons.size(); ++i) {
        int bestPenalty = std::numeric_limits<int>::max();
        record bestRecord{};
        bool found = false;

        for (int d = 0; d < s.days; ++d) {
            for (int t = 0; t < s.timeslots; ++t) {
                for (size_t r = 0; r < s.data.rooms.size(); ++r) {

                    // Only compatible rooms
                    if (s.data.rooms[r].type !=
                        s.data.lessons[i].requiredRoom)
                        continue;

                    record candidate{
                        static_cast<int>(r), t, d
                    };

                    // Temporary assignment
                    result.push_back(candidate);

                    int penalty = greedy::calculate_penalty(result, s);

                    result.pop_back();

                    if (penalty < bestPenalty) {
                        bestPenalty = penalty;
                        bestRecord = candidate;
                        found = true;
                    }
                }
            }
        }

        if (!found)
            throw std::runtime_error(
                "No compatible room for a lesson"
            );

        result.push_back(bestRecord);
    }

    return result;
}


namespace greedy {

    int calculate_penalty(
        const std::vector<record>& records,
        Schedule& s
    ) {
        if (records.size() > s.data.lessons.size())
            throw std::invalid_argument("Too many records");

        constexpr int hard_v = 1000;
        constexpr int soft_v = 50;

        int penalty = 0;

        std::map<int, std::vector<std::vector<int>>> groupSchedule;

        for (size_t i = 0; i < records.size(); ++i) {
            const record& r1 = records[i];
            const lesson& l1 = s.data.lessons[i];

            if (r1.day < 0 || r1.day >= s.days ||
                r1.timeslot < 0 || r1.timeslot >= s.timeslots ||
                r1.room_id < 0 ||
                static_cast<size_t>(r1.room_id) >= s.data.rooms.size()) {
                throw std::out_of_range("Invalid assignment");
            }

            for (size_t j = i + 1; j < records.size(); ++j) {
                const record& r2 = records[j];
                const lesson& l2 = s.data.lessons[j];

                if (r1.day != r2.day ||
                    r1.timeslot != r2.timeslot)
                    continue;

                // Hard constraints
                if (r1.room_id == r2.room_id)
                    penalty += hard_v;

                if (l1.teacher_id == l2.teacher_id)
                    penalty += hard_v;

                if (l1.group_id == l2.group_id)
                    penalty += hard_v;
            }

            if (l1.requiredRoom != s.data.rooms[r1.room_id].type)
                penalty += hard_v;

            if (!groupSchedule.contains(l1.group_id)) {
                groupSchedule[l1.group_id] =
                    std::vector<std::vector<int>>(
                        s.days, std::vector<int>(s.timeslots, 0)
                    );
            }

            groupSchedule[l1.group_id][r1.day][r1.timeslot]++;
        }

        for (const auto& [group, sh] : groupSchedule) {
            for (const auto& day : sh) {
                bool had_lesson = false;
                int gaps = 0;
                int count = 0;

                // Windows
                for (int slot : day) {
                    if (slot > 0) {
                        if (had_lesson)
                            penalty += soft_v * gaps;

                        had_lesson = true;
                        gaps = 0;
                        ++count;
                    }
                    else if (had_lesson) {
                        ++gaps;
                    }
                }

                // Daily overload
                if (count > 3)
                    penalty += soft_v * (count - 3);
            }
        }

        return penalty;
    }

    void printOutput(const std::vector<record>& records, Schedule& s)
    {
        std::vector<std::vector<std::vector<geneOutput>>> table(
            s.days,
            std::vector<std::vector<geneOutput>>(s.timeslots)
        );

        for (size_t i = 0; i < records.size(); ++i) {
            const record& r = records[i];
            const lesson& l = s.data.lessons[i];

            table[r.day][r.timeslot].push_back(
                geneOutput(r, l)
            );
        }

        printOutput(table);

    }
}