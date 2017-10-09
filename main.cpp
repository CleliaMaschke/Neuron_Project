#include "Neuron.hpp"
#include <iostream>
#include <fstream>

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
	
	double simtime(time_start);
	Neuron n;
	
	std::ofstream fichier("Neuron.txt");
	
	if( time_start <= simtime < time_stop )  //condition [time_start, time_stop[
	{ 	
		n.getTime_(time_start);
		while(simtime < time_stop) {
			simtime += dt;
			n.update(dt, Iext);
			if(!fichier.fail()) {
				fichier << "Time : " << simtime << std::endl;
				fichier << "Membrane potential : " << n.getMembranePotential() << std::endl;
			} else {
				std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
			}	
			/*std::cout << "Le temps est :" << simtime << std::endl;
			std::cout << "Le potentiel est de : " << n.getMembranePotential() << std::endl;
		*/}
	} else {
		Iext = 0.0;
	}
	
	fichier.close();
	std::cout << "Time when the spikes occured: " << std::endl;
	n.getTimeSpike();
	
	return 0;
}

	
