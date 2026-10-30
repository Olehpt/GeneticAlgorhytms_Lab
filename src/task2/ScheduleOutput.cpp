#include "ScheduleOutput.h"
#include <iostream>

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
