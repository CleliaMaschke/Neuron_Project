#ifndef Cortex_HPP
#define Cortex_HPP
#include <iostream>
#include <vector>
#include <cassert>
#include "Neuron.hpp"
#include <cmath>
#include <fstream>
#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

class Cortex
{
	private :
	
		#ifdef TEST
	FRIEND_TEST (neuron_test, calculate_potential);
	FRIEND_TEST (neuron_test, time_spikes); 
		#endif 
	
	//Number total of neuron
	const unsigned int Number_Neurons_ = 2;
	
	
	
	//Increase potential of other neuron 
	const double J = 0.1;
	
	//dt
	//const double dt = 0.1;
	
	//Time of the programm
	double Clock_ = 0.0;
	
	//nombre de step
	long Step_Clock_ = 0;
	
	//fin du temps 
	long Step_End; 
	
	public : 
	
	//Initialise le nombre de neurones
	std::vector<Neuron*> neurons;
	
	//Constructor
	Cortex();
	
	//Destructor
	~Cortex(); 
	
	//constructreur de copie
	Cortex(Cortex const& other); 
	
	//Initialie l'ensemble des vecteurs
	void initialise_neuron(long start, double Iext);
	
	//Update the neuron state / potential in time dt
	void update_neuron(long Step_start, long Step_end);
	
	//write potential, time in a file
	void load_from_file();
	
	//write the time when spike occures
	void time_spike();
	
	//Initialise the clock 
	void setClock(double clock);
	
	//Supprime les neurones 
	void Reset();
	
	//Initialise le step du programme principal
	void setStepClock(long num);
	
	//Initiliase la fin du programme 
	void setStepEnd(long num);
	
	//Ajoute l'input au neurons
	void setNeuronInput(int i, double Input);
	
};

#endif
