#include "Neuron.hpp"
#include "Cortex.hpp"
#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

TEST(neuron_test, calculate_potential) {
	
	Neuron neuron(0.1);
	neuron.set_i_ext(1.0);
	neuron.resizeRingBuffer(1);
	
	//First update test with dt = 0.1 and step start = 1000 
	neuron.update(1000);
	EXPECT_EQ(((20.0*(1.0 - exp(-0.1/20.0))) - neuron.getMembranePotential()), 0);
	
	//Test for 3000 update
	for(long i(0); i < 3000; ++i) {
		neuron.update(1000);
	}
	
	//Iext = 1.0 -> no spike but membrane potential near 20
	EXPECT_LT(neuron.getMembranePotential(), 20.0);
}

TEST(neuron_test, time_spikes) 
{
	
	Cortex cortex;
	//time start = 100ms and Iext = 1.01
	cortex.setStepClock(1000);
	cortex.setStepEnd(4000);
	cortex.initialise_neuron(0, 1.01, 0.5);
	cortex.setNeuronInput(0, 1.01);
	cortex.setNeuronInput(1, 0.0);
	
	for(long i(1000); i <= 4000; ++i) {
		cortex.update_neuron(1000, 4000, 2);
	}
	
	EXPECT_EQ(cortex.neurons[0]->time_spike.size(), 3);
	EXPECT_FLOAT_EQ(cortex.neurons[0]->time_spike[0], 192.4);
	EXPECT_FLOAT_EQ(cortex.neurons[0]->time_spike[1], 286.8);
	EXPECT_FLOAT_EQ(cortex.neurons[0]->time_spike[2], 381.2);
	
	EXPECT_EQ(cortex.neurons[1]->time_spike.size(), 0);
	
}
	

int main (int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
