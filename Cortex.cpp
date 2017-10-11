#include "Cortex.hpp"
#include <cmath>

/*Cortex::Cortex()
: Clock_(0.0) {}

Cortex::~Cortex() {}

Cortex(Cortex const& other) {}*/

void Cortex::initialise_neuron(double t_start)
{
	for(int i(0); i < Number_Neurons_; ++i) 
	{ 
		neurons.push_back(new Neuron);
		neurons[i]->getTime_(t_start);
		
	}
}

void Cortex::update_neuron(double t_start, double t_stop, double Iext) 
{
	if( (t_start <= Clock_) and (Clock_ < t_stop ))  //condition [time_start, time_stop[
	{ 
		while(Clock_ < t_stop) {
			for(int i(0); i < neurons.size(); ++i) {
				bool spikeneuro(neurons[i]->update(dt, Iext, t_start));
				if(spikeneuro and (i+1) < neurons.size()) {
					neurons[i+1]->sumInput(J);
				}
			}
			Clock_ += dt;
		}
	} else {
		Iext = 0.0;
	}
}

void Cortex::load_from_file() {
	std::ofstream fichier("Neuron.txt");
	for(int i(0); i < neurons.size(); ++i) {
	if(!fichier.fail()) {
					fichier << "Time : " << Clock_ << std::endl;
					fichier << "Membrane potential : " << neurons[i]->getMembranePotential() << std::endl;
				} else {
					std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
				}	
	fichier.close();
	
	}
}

void Cortex::time_spike() 
{
	std::ofstream fichier("Time_Spike.txt");
	if(!fichier.fail()) {
		for(int i(0); i < neurons.size(); ++i) {
			std::cout << "Time when the spikes occured for neuron: " << i << std::endl;
			neurons[i]->getTimeSpike();
		}
	}
	fichier.close();
}

void Cortex::setClock(double clock)
{
	Clock_  = clock;
	
}
	
