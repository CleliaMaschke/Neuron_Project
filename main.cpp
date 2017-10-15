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
	
	Cortex c;

	c.setClock(time_start);
	std::cout << "SetClock()" << std::endl;
	c.initialise_neuron(time_start);
	std::cout << "Initialise neurones" << std::endl;
	c.update_neuron(time_start, time_stop, Iext);
	std::cout << "Update neuron" << std::endl;
	c.time_spike();
	std::cout << "Time spike" << std::endl;
	c.Reset();
	std::cout << "Reset()" << std::endl;

	
	return 0;
}

	
