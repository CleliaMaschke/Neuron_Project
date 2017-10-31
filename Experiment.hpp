#ifndef Experiment_HPP
#define Experiment_HPP
#include <iostream>
#include <vector>
#include <cassert>
#include "Cortex.hpp"
#include <cmath>
#include <fstream>
#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

class Experiment
{
	private :
	
	double g_; /*! ratio Ji/Je */
	double n_; /*! ratio Vext/Vthr */
	
	public:
	
	/**	Run all the programm
	 * @param : &fiche is the file where the time of the spike for each neuron is noted 
	 */
	void run_programme(double g, double eta, long start, long stop, double I, std::ofstream &fiche);
	
};

#endif
