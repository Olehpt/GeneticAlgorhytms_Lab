#pragma once
#include "Schedule.h"

inline const std::vector<std::string> subjects = {
	"Math",
	"Physics",
	"English",
	"Programming",
	"Computer architecture",
	"Databases"
};

inline const std::vector<std::string> teachers = {
	"Teacher A",
	"Teacher B",
	"Teacher C",
	"Teacher D",
};

inline const std::vector<std::string> groups = {
	"Group 1",
	"Group 2",
	"Group 3",
	"Group 4",
};

inline const std::vector<lesson> lessons = { //group, teacher, subject, roomtype
	{0, 0, 0, roomType::Lecture},
	{1, 1, 1, roomType::Computer},
	{2, 2, 2, roomType::Regular},
	{3, 3, 3, roomType::Lecture},
	{0, 0, 4, roomType::Computer},
	{1, 1, 5, roomType::Regular},
	{2, 2, 5, roomType::Lecture},
	{3, 3, 1, roomType::Computer},
	{0, 0, 2, roomType::Regular},
	{1, 1, 4, roomType::Lecture}
};

inline const std::vector<room> rooms = {
	{"Room 101", roomType::Lecture},
	{"Room 102", roomType::Computer},
	{"Room 103", roomType::Regular},
	{"Room 104", roomType::Lecture},
	{"Room 105", roomType::Computer}
};