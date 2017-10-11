#ifndef Cortex_HPP
#define Cortex_HPP
#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include <fstream>
#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

class Cortex
{
	private :
	
	//Number total of neuron
	const unsigned int Number_Neurons_ = 2;
	
	//Initialise le nombre de neurones
	std::vector<Neuron*> neurons;
	
	//Increase potential of other neuron 
	const double J = 0.1;
	
	//dt
	const double dt = 0.1;
	
	//Time of the programm
	double Clock_;
	
	public : 
	
	//Constructor
	/*Cortex();
	
	//Destructor
	~Cortex(); 
	
	//constructreur de copie
	Cortex(Cortex const& other); */
	
	//Initialie l'ensemble des vecteurs
	void initialise_neuron(double t_start);
	
	//Update the neuron state / potential in time dt
	void update_neuron(double t_start, double t_stop, double Iext);
	
	//write potential, time in a file
	void load_from_file();
	
	//write the time when spike occures
	void time_spike();
	
	//Initialise the clock 
	void setClock(double clock);
	
	
	
	
};

#endif
