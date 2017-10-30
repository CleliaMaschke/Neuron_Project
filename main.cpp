#include "Neuron.hpp"
#include "Cortex.hpp"
#include <iostream>
#include <fstream>
#include <vector>


int main ()
{
	double time_start;
	double time_stop;
	std::cout << "Time interval for the experience (in second) from : ";
	std::cin >> time_start;
	std::cout << " to ";
	std::cin >> time_stop;
	double Iext; 
	std::cout << "Which is Iext during this time? ";
	std::cin >> Iext;
	
	long step_start = time_start / dt;
	long step_end = time_stop / dt;
	
	Cortex c;

	c.setClock(time_start);
	//std::cout << "SetClock()" << std::endl;
	
	c.setStepClock(step_start);
	
	c.setStepEnd(step_end);
	
	c.initialise_neuron(step_start, Iext);
	std::cout << "Initialise neurones" << std::endl;
	
	c.Initialise_Connexions();
	std::cout << "Initialise Connexions" << std::endl;
	
	c.update_neuron(step_start, step_end);
	std::cout << "Update neuron" << std::endl;
	
	c.time_spike();	
	
	c.Save_to_file();
	std::cout << "Time spike" << std::endl;
	
	c.Document_Python();
	std::cout << "Document python" << std::endl;
	
	c.Reset();
	std::cout << "Reset()" << std::endl;

	
	return 0;
}

	
