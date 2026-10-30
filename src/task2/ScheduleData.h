#pragma once
#include "Schedule.h"

inline const std::vector<std::string> subjects = {
	"Math", "Physics", "English", "Programming", "Computer architecture",
	"Databases", "Algorithms", "Operating systems", "Networks", "Statistics"
};

inline const std::vector<std::string> teachers = {
	"Teacher A", "Teacher B", "Teacher C", "Teacher D", "Teacher E", "Teacher F"
};

inline const std::vector<std::string> groups = {
	"Group 1", "Group 2", "Group 3", "Group 4"
};

inline const std::vector<room> rooms = {
	{"Room 101", roomType::Lecture},
	{"Room 102", roomType::Computer},
	{"Room 103", roomType::Regular},
	{"Room 104", roomType::Lecture},
	{"Room 105", roomType::Computer}
};

inline const std::vector<lesson> lessons = { //group, teacher, subject, roomtype
    {0, 0, 0, roomType::Lecture},
    {1, 1, 1, roomType::Computer},
    {2, 2, 2, roomType::Regular},
    {3, 3, 3, roomType::Lecture},
    {0, 4, 4, roomType::Computer},
    {1, 5, 5, roomType::Regular},
    {2, 0, 6, roomType::Lecture},
    {3, 1, 7, roomType::Computer},
    {0, 2, 8, roomType::Regular},
    {1, 3, 9, roomType::Lecture}
};

inline const _Schedule data(lessons, rooms, groups, subjects, teachers);
