#pragma once
#include <gapp/gapp.hpp>
#include "Schedule.h"
#include "ScheduleData.h"

#define TEMPCONST 10

class T2 : public gapp::FitnessFunction<gapp::IntegerGene, TEMPCONST> {
	gapp::FitnessVector invoke(const gapp::Candidate<gapp::IntegerGene>& c) const override;
	//
	Schedule& s;
public:
	explicit T2(Schedule& sch) : s(sch) {}
};

void task2_solve();