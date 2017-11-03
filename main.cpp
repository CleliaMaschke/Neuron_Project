#include "Neuron.hpp"
#include "Cortex.hpp"
#include "Experiment.hpp"
#include <iostream>
#include <fstream>
#include <vector>


int main ()
{
	double time_start;
	double time_stop;
	/*std::cout << "Time interval for the experience (in second) from : ";
	std::cin >> time_start;
	std::cout << " to ";
	std::cin >> time_stop;*/
	double Iext; 
	std::cout << "Which is Iext during this time? ";
	std::cin >> Iext;
	
	long step_start = time_start / dt;
	long step_end = time_stop / dt;
	
	/**
	 * We will draw the 4 plots 
	 * */
	
	Experiment E_;
	
	/*std::ofstream fichierx("Param1.csv");
	E_.run_programme(3.0, 2.0, 5000, 6000, Iext, fichierx);
	fichierx.close();
	
	std::ofstream fichiery("Param2.csv");
	E_.run_programme(6.0, 4.0, 10000, 12000, Iext, fichiery);
	fichiery.close();*/
	
	std::ofstream fichierz("Param3.csv");
	E_.run_programme(5.0, 2.0, 10000, 12000, Iext, fichierz);
	fichierz.close();
	
	/*std::ofstream fichierw("Param4.csv");
	E_.run_programme(4.5, 0.9, 10000, 12000, Iext, fichierw);
	fichierw.close();*/
	
	return 0;
}

	
