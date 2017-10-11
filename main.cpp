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
	c.initialise_neuron(time_start);
	c.update_neuron(time_start, time_stop, Iext);
	c.time_spike();

	
	return 0;
}

	
