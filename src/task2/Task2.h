#pragma once
#include <gapp/gapp.hpp>
#include "Schedule.h"
#include "ScheduleData.h"

#define TEMPCONST 20

class T2 : public gapp::FitnessFunction<gapp::IntegerGene, TEMPCONST> {
	gapp::FitnessVector invoke(const gapp::Candidate<gapp::IntegerGene>& c) const override;
	Schedule& s;
public:
	explicit T2(Schedule& sch) : s(sch) {}
};

void task2_solve(int p, double c, double m, int generations);
void task2_metric(int p, double c, double m, int generations, const std::string& fileoutput);

