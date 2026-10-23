#pragma once
#include <gapp/gapp.hpp>
#include "Schedule.h"
#include "ScheduleData.h"

#define TEMPCONST 35

class T2 : public gapp::FitnessFunction<gapp::IntegerGene, TEMPCONST> {
	gapp::FitnessVector invoke(const gapp::Candidate<gapp::IntegerGene>& c) const override;
	//
	Schedule& s;
public:
	explicit T2(Schedule& sch) : s(sch) {}
};

void task2_solve(int p, double c, double m, int generations);

struct geneOutput {
	record r;
	lesson l;
};

std::string roomTypeConvert(int id);
void printOutput(std::vector<std::vector<std::vector<geneOutput>>>& table);
void printOutputAsArray(std::vector<std::vector<std::vector<geneOutput>>>& table);