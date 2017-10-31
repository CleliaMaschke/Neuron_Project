#include "Experiment.hpp"
#include <cmath>
#include <random>

void Experiment::run_programme(double g, double eta, long start, long stop, double I, std::ofstream &fiche)
{
	g_ = g;
	n_ = eta;
	
	double Jin = g_ * 0.1; /*! Initialise J inhibitor */
	Cortex c;
	
	c.setClock(start);
	//std::cout << "SetClock()" << std::endl;
	
	c.setStepClock(start);
	
	c.setStepEnd(stop);
	
	c.initialise_neuron(start, I, Jin);
	std::cout << "Initialise neurones" << std::endl;
	
	c.Initialise_Connexions();
	std::cout << "Initialise Connexions" << std::endl;
	
	c.update_neuron(start, stop, n_);
	std::cout << "Update neuron" << std::endl;
	
	//c.time_spike();	
	
	/*c.Save_to_file();
	std::cout << "Time spike" << std::endl;*/
	
	c.Document_Python(fiche);
	std::cout << "Document python" << std::endl;
	
	c.Reset();
	std::cout << "Reset()" << std::endl;
}
