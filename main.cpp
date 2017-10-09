
#include "Neuron.hpp"
#include <iostream>
#include <fstream>
#include <vector>

int main ()
{
	double time_start = 0.0;
	double time_stop = 0.1;
	std::cout << "Time interval for the experience (in second) from : ";
	std::cin >> time_start;
	std::cout << " to ";
	std::cin >> time_stop;
	double dt = 0.1; //h = pas de simulation
	double Iext = 1.0; 
	std::cout << "Which is Iext during this time? ";
	std::cin >> Iext;
	std::cout << "How many neurons ?";
	int number_neurons = 0;
	std::cin >> number_neurons;
	
	double simtime(time_start);
	std::vector<Neuron*> neurons;
	const double J = 0.1;
	
	for(int i(0); i < number_neurons; ++i) 
	{ 
		neurons.push_back(new Neuron);
		neurons[i]->getTime_(time_start);
		
	}
	
	std::ofstream fichier("Neuron.txt");
	
	if( (time_start <= simtime) and (simtime < time_stop ))  //condition [time_start, time_stop[
	{ 	
		
			
		while(simtime < time_stop) {
			simtime += dt;
			for(int i(0); i < neurons.size(); ++i) {
				bool spikeneuro(neurons[i]->update(dt, Iext));
				if(spikeneuro and i+1 < neurons.size()) {
					neurons[i+1]->sumInput(J);
				}
				if(!fichier.fail()) {
					fichier << "Time : " << simtime << std::endl;
					fichier << "Membrane potential : " << neurons[i]->getMembranePotential() << std::endl;
				} else {
					std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
				}		
			}
		}
	} else {
		Iext = 0.0;
	}
	
	fichier.close();
	
	
	for(int i(0); i < neurons.size(); ++i) {
		std::cout << "Time when the spikes occured for neuron: " << i << std::endl;
		neurons[i]->getTimeSpike();
	}
	
	return 0;
}

	
