#include "Schedule.h"
#include <iostream>

Schedule::Schedule(_Schedule sch) : data(sch) {
	lessons_size = this->data.lessons.size();
};

int Schedule::get_size() {
	return lessons_size;
}

int Schedule::codegen(int d, int t, int r) {
	return (t + d * timeslots) * data.rooms.size() + r;
}

record Schedule::decode(int code) {
	int r = code % data.rooms.size();
	int t = (code - r)/data.rooms.size() % timeslots;
	int d = ((code - r) / data.rooms.size() - t) / timeslots;
	return {r, t, d};
}

int calculate_penalty(const std::vector<int>& c, Schedule& s) {
	if (c.size() != s.data.lessons.size()) {
		std::cout << "error occured\n";
		return 0;
	}
	int penalty = 0;
	const int hard_v = 1000;
	const int soft_v = 50;
	std::vector<record> decoded_genes;
	for (auto _c : c) {
		decoded_genes.push_back(s.decode(_c));
	}
	for (size_t i = 0; i < decoded_genes.size(); i++) {
		const record& r1 = decoded_genes[i];
		const lesson& l1 = s.data.lessons[i];
		for (size_t j = i + 1; j < decoded_genes.size(); j++) {
			const record& r2 = decoded_genes[j];
			const lesson& l2 = s.data.lessons[j];
			//room conflict (hard)
			if (r1.day == r2.day && r1.timeslot == r2.timeslot && r1.room_id == r2.room_id) {
				penalty += hard_v;
			}
			//teacher conflict (hard)
			if (l1.teacher_id == l2.teacher_id && r1.day == r2.day && r1.timeslot == r2.timeslot) {
				penalty += hard_v;
			}
			//group conflict (hard)
			if (l1.group_id == l2.group_id && r1.day == r2.day && r1.timeslot == r2.timeslot) {
				penalty += hard_v;
			}
		}
		//room type mismatch (hard)
		if (l1.requiredRoom != s.data.rooms[r1.room_id].type) {
			penalty += hard_v;
		}
	}
	//
	std::map<int, std::vector<std::vector<int>>> groupSchedule;
	for (size_t i = 0; i < decoded_genes.size(); i++) {
		int group = s.data.lessons[i].group_id;
		if (!groupSchedule.contains(group)) {
			groupSchedule[group] = std::vector<std::vector<int>>(s.days, std::vector<int>(s.timeslots, 0));
		}
		const record& r = decoded_genes[i];
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