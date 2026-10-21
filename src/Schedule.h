#pragma once
#include <vector>
#include <string>
#include <map>
#include <array>

enum class roomType {
	Lecture,
	Computer,
	Regular
};

struct lesson {
	int group_id;
	int teacher_id;
	int subject_id;
	roomType requiredRoom;
};

struct room {
	std::string name;
	roomType type;
};

struct record { //gene
	int room_id;
	int timeslot;
	int day;
};

struct _Schedule {
	const std::vector<lesson>& lessons;
	const std::vector<room>& rooms;
	const std::vector<std::string>& groups, & subjects, & teachers;
};

class Schedule {
public:
	_Schedule data;
	int lessons_size;
	static const int days = 5, timeslots = 5;
	Schedule(_Schedule data);
	int get_size();

	int codegen(int d, int t, int r);
	record decode(int code);

	friend int calculate_penalty(const std::vector<int>& c, Schedule& s);
};