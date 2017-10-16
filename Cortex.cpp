
#include "Cortex.hpp"
#include <cmath>

Cortex::Cortex() {};

Cortex::~Cortex() {};

Cortex::Cortex(Cortex const& other)
: neurons(other.neurons) {};

void Cortex::initialise_neuron(double t_start)
{
	for(int i(0); i < Number_Neurons_; ++i) 
	{ 
		neurons.push_back(new Neuron);
		neurons[i]->getTime_(t_start);
		neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
		
	}
}


void Cortex::update_neuron(double t_start, double t_stop, double Iext) 
{	
	
	if( (t_start <= Clock_) and (Clock_ < t_stop ))  //condition [time_start, time_stop[
	{ 
		
		while(Clock_ < t_stop) {
			for(int i(0); i < neurons.size(); ++i) {
				std::cout << "Time stop" << t_stop << std::endl;
				std::cout << "Dans la boucle update_neuron" << std::endl;
				bool spikeneuro(neurons[i]->update(dt, Iext, t_start));
				if(spikeneuro and (i+1) < neurons.size()) {
					std::cout << "if dans update_neuron" << std::endl;
					//neurons[i+1]->sumInput(J);
					size_t m = neurons[i+1]->getRingBuffer().size();
					std::cout << "taille de Ring_Buffer_ : " << m << std::endl;
					//int num = neurons[i+1]->getStep();
					neurons[i+1]->setRingBuffer(Step_Clock_ % (m-1), J);
				}
			}
			++Step_Clock_ ;
			Clock_ = Step_Clock_ * dt + t_start;
			std::cout << "Step_clock : " << Step_Clock_ << std::endl;
		}
	} else {
		Iext = 0.0;
	}
	
	std::cout << "Clock: " << Clock_ << std::endl;
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

void Cortex::Reset()
{
	for(auto& neuron : neurons)
	{
		delete neuron;
		neuron = nullptr;
	}
	
	neurons.clear();
}



