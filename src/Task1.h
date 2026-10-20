#pragma once
#include <gapp/gapp.hpp>
#include <iostream>

double func(double x, double y);

class T1 : public gapp::FitnessFunction<gapp::RealGene, 2> {
	gapp::FitnessVector invoke(const gapp::Candidate<gapp::RealGene>& c) const override;
};

void task1_solve();