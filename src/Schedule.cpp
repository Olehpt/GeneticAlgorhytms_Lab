#include "Schedule.h"
#include <iostream>
#include <map>

int codegen(int d, int t, int r) {
	return (t + d * TIMESLOTS) * rooms.size() + r;
}

record decode(int code) {
	int r = code % rooms.size();
	int t = (code - r)/rooms.size() % TIMESLOTS;
	int d = ((code - r) / rooms.size() - t) / TIMESLOTS;
	return {r, t, d};
}

int calculate_penalty(const std::vector<int>& c, const std::vector<lesson>& l) {
	if (c.size() != l.size()) {
		std::cout << "error occured\n";
		return -1;
	}
	int penalty = 0;
	const int hard_v = 1000;
	const int soft_v = 50;
	std::vector<record> schedule;
	for (auto _c : c) {
		record r = decode(_c);
		schedule.push_back(r);
	}
	for (size_t i = 0; i < schedule.size(); i++) {
		const record& r1 = schedule[i];
		const lesson& l1 = l[i];
		for (size_t j = i + 1; j < schedule.size(); j++) {
			const record& r2 = schedule[j];
			const lesson& l2 = l[j];
			//room conflict (hard)
			if (r1.day == r2.day && r1.timeslot == r2.timeslot && r1.roomid == r2.roomid) {
				penalty += hard_v;
			}
			//teacher conflict (hard)
			if (l1.teacher == l2.teacher && r1.day == r2.day && r1.timeslot == r2.timeslot) {
				penalty += hard_v;
			}
			//group conflict (hard)
			if (l1.group == l2.group && r1.day == r2.day && r1.timeslot == r2.timeslot) {
				penalty += hard_v;
			}
		}
		//room type mismatch (hard)
		if (l1.requiredRoom != rooms[r1.roomid].type) {
			penalty += hard_v;
		}
	}
	//
	std::map<int, std::vector<std::vector<int>>> groupSchedule;
	for (size_t i = 0; i < schedule.size(); i++) {
		int group = l[i].group;
		if (!groupSchedule.contains(group)) {
			groupSchedule[group] = std::vector<std::vector<int>>(DAYS, std::vector<int>(TIMESLOTS, 0));
		}
		const record& r = schedule[i];
		groupSchedule[group][r.day][r.timeslot]++;
	}
	for (const auto& [group, sh] : groupSchedule) {
		for (auto day : sh) {
			bool had_lesson = 0;
			int count = 0;
			//windows
			for (int slot : day) {
				if (slot > 0) {
					if (had_lesson) {
						penalty += soft_v * count;
					}
					had_lesson = true;
					count = 0;
				}
				else if (had_lesson) {
					count++;
				}
			}
			//too many lesson in a day
			count = 0;
			for (int slot : day) {
				if (slot > 0) count++;
			}
			if (count > 3) penalty += soft_v * (count - 3);
		}
	}
	return penalty;
}