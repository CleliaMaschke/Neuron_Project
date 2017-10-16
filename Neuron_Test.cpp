#include "Neuron.hpp"
#include <iostream>
#include <cmath>
#include <gtest/gtest.h>

TEST(Neuron_Test, calculate_potential) {
	/*Neuron n1;
	Neuron n2;
	n1.potential = potential_seuil + 1;
	n2.potential = 0.0;
	n1.Iext = 1.01;
	n1.update(0.2, 100);
	EXPECT_EQ(n2.potential, J);*/
	Neuron neuron(1.0);
	//First update test
	neuron.update(0.1, 100);
	EXPECT_EQ(((20.0*(1.0-std::exp(-0.1/20.0))) - neuron.getMembranePotential()), 0);
}

int main (int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
