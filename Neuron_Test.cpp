#include "Neuron.hpp"
#include "Cortex.hpp"
#include "Cortex.hpp"
#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

TEST(oneNeuron, calculate_potential) {
	
	Neuron neuron(0.1);
	neuron.set_i_ext(1.0);
	neuron.resizeRingBuffer(1);
	
	//First update test with dt = 0.1 and step start = 1000 
	neuron.update(1000, 0);
	EXPECT_EQ(((20.0*(1.0 - exp(-0.1/20.0))) - neuron.getMembranePotential()), 0);
	
	//Test for 3000 update
	for(long i(0); i < 3000; ++i) {
		neuron.update(1000, 0);
	}
	
	//Iext = 1.0 -> no spike but membrane potential near 20
	EXPECT_LT(neuron.getMembranePotential(), 20.0);
}

TEST(oneNeuron, time_spikes) 
{
	Neuron neuron_(0.1);
	neuron_.set_i_ext(1.01);
	neuron_.resizeRingBuffer(1);
	for(long i(1000); i <= 4000; ++i) {
		neuron_.update(i, 0);
	}
	
	EXPECT_EQ(neuron_.getTimeSpikeVector().size(), 3);
	EXPECT_FLOAT_EQ(neuron_.getTimeSpikeVector()[0], 192.4);
	EXPECT_FLOAT_EQ(neuron_.getTimeSpikeVector()[1], 286.8);
	EXPECT_FLOAT_EQ(neuron_.getTimeSpikeVector()[2], 381.2);
	
}

TEST(twoNeuron, Connexion_with_oneSpike) 
{
	//Each neuron is excitatory with J = 0.1
	Neuron n1(0.1); 
	Neuron n2(0.1);
	
	//First neuron recieve an Input externe
	n1.set_i_ext(1.01);
	long D = n1.getDelay() / 0.1;
	
	//Resize the buffer
	n1.resizeRingBuffer(n1.getDelay() / 0.1 + 1);
	n2.resizeRingBuffer(n2.getDelay() / 0.1 + 1);
	//std::cout << "Size of ring buffer : " << n2.getRingBuffer().size() << std::endl;
	
	std::ofstream fichier("Neuron_test.txt");
	
	
	size_t m = n2.getRingBuffer().size();
	//First spike at 924 steps + 15 steps of delay
	
	if(!fichier.fail()) {
	for(long i(0); i < 940; ++i) {
		if(n1.update(i, 0)) { //update neuron 1 and test if he spikes 
			
			n2.setRingBuffer((i + D) % m, n1.getJ()); //neuron 2 s tores J in his buffer
			/*std::cout << "Ring buffer [1] : " << n2.getRingBuffer()[0] << std::endl;
			std::cout << "Ring buffer [2] : " << n2.getRingBuffer()[1] << std::endl;
			std::cout << "Ring buffer [3] : " << n2.getRingBuffer()[2] << std::endl;
			std::cout << "Ring buffer [4] : " << n2.getRingBuffer()[3] << std::endl;
			std::cout << "Ring buffer [5] : " << n2.getRingBuffer()[4] << std::endl;
			std::cout << "Ring buffer [6] : " << n2.getRingBuffer()[5] << std::endl;
			std::cout << "Ring buffer [7] : " << n2.getRingBuffer()[6] << std::endl;
			std::cout << "Ring buffer [8] : " << n2.getRingBuffer()[7] << std::endl;
			std::cout << "Ring buffer [9] : " << n2.getRingBuffer()[8] << std::endl;
			std::cout << "Ring buffer [10] : " << n2.getRingBuffer()[9] << std::endl;
			std::cout << "Ring buffer [11] : " << n2.getRingBuffer()[10] << std::endl;
			std::cout << "Ring buffer [12] : " << n2.getRingBuffer()[11] << std::endl;
			std::cout << "Ring buffer [13] : " << n2.getRingBuffer()[12] << std::endl;
			std::cout << "Ring buffer [14] : " << n2.getRingBuffer()[13] << std::endl;
			std::cout << "Ring buffer [15] : " << n2.getRingBuffer()[14] << std::endl;
			std::cout << "Ring buffer [16] : " << n2.getRingBuffer()[15] << std::endl;*/
			EXPECT_EQ(n1.getMembranePotential(), 0.0); //Neuron 1 has a spike so he has a membrane potential = 0.0
		}
		
		fichier << "membrane potential n1 = " << n1.getMembranePotential() << std::endl;
		n2.update(i, 0);
		fichier << "membrane potential n2 = " << n2.getMembranePotential() << std::endl;
	}
	} else {
			std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
		}
	
	fichier.close();  
	EXPECT_FLOAT_EQ(n2.getMembranePotential(), 0.1); //neuron 2 hase a +J because neuron 1 has spiked
}

TEST(twoNeurons, Connexion_with_twoSpikes)
{
	Neuron n1(0.1);
	Neuron n2(0.1);
	n1.set_i_ext(1.01);
	n2.set_i_ext(1.0);
	
	
	n1.resizeRingBuffer(n1.getDelay() / 0.1 + 1);
	n2.resizeRingBuffer(n2.getDelay() / 0.1 + 1);
	long D = n1.getDelay() / 0.1;
	std::cout << "Neurone 1" << std::endl;
	std::ofstream fichierx("Neuron_test_2.txt");
	if(!fichierx.fail()) {
	//Neuron 2 1st spike should occur right after neuron 1 2nd spike
	for (long i(0); i < 1884; ++i) { //number of steps for neuron 1 to spike twice (1868 steps) + delay (15 steps)
		if (n1.update(i, 0)) { //update neuron 1
			size_t m = n2.getRingBuffer().size();
			n2.setRingBuffer((i + D) % m, n1.getJ()); //neuron 2 stores J in his buffer
			EXPECT_EQ(n1.getMembranePotential(), 0.0);
		}
		fichierx << "Potential Neurone 1 = " << n1.getMembranePotential() << std::endl;
		n2.update(i, 0);
		fichierx << "Potential Neurone 2 = " << n2.getMembranePotential() << std::endl;
	}
	} else {
			std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
		}
	
	fichierx.close();
	
	//neuron 2 has no spike yet
	EXPECT_EQ(n2.getTimeSpikeVector().size(), 0);
	n2.update(1884, 0);
	//neuron 2 spike
	EXPECT_EQ(n2.getMembranePotential(), 0.0);
	EXPECT_EQ(n2.getTimeSpikeVector().size(), 1);
}

TEST(cortex, test_connexions) 
{
	Cortex c;
	c.initialise_neuron(0, 0.0, -0.5);
	EXPECT_EQ(c.getSizeNeurons(), 12500);
}

int main (int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
