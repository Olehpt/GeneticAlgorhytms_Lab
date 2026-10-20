#pragma once
#include <vector>

enum class roomType {
	Lecture,
	Computer,
	Regular
};

enum class subject {
	Math,
	Physics,
	English,
	Programming
};

struct lesson {
    int group;
    int teacher;
    subject s;
    roomType requiredRoom;
};

struct room {
	int id;
	roomType type;
};

struct record {
    int roomid;
    int timeslot;
    int day;
};

int codegen(int d, int t, int r);
record decode(int code);

int calculate_penalty(const std::vector<int>& c, const std::vector<lesson>& l);

//constants & data

const int DAYS = 5;
const int TIMESLOTS = 5;

const int NUM_ROOMS = 8; //?
const int NUM_LESSONS = 8;
const int NUM_GROUPS = 4;
const int NUM_TEACHERS = 8;

inline std::vector<room> rooms = {
	{0, roomType::Lecture},
	{1, roomType::Lecture},
	{2, roomType::Computer},
	{3, roomType::Computer},
	{4, roomType::Regular},
	{5, roomType::Regular},
	{6, roomType::Regular},
	{7, roomType::Regular}
};


inline std::vector<lesson> lessons = {
	{0, 0, subject::Math, roomType::Lecture},
	{0, 1, subject::Physics, roomType::Lecture},
	{1, 2, subject::English, roomType::Regular},
	{1, 3, subject::Programming, roomType::Computer},
	{2, 4, subject::Math, roomType::Lecture},
	{2, 5, subject::Physics, roomType::Lecture},
	{3, 6, subject::English, roomType::Regular},
	{3, 7, subject::Programming, roomType::Computer}
};