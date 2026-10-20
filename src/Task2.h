#pragma once
#include <gapp/gapp.hpp>
#include "Schedule.h"

class T2 : public gapp::FitnessFunction<gapp::IntegerGene, NUM_LESSONS> {
	gapp::FitnessVector invoke(const gapp::Candidate<gapp::IntegerGene>& c) const override;
};

void task2_solve();