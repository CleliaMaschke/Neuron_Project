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
	
		#endif   
	
	const unsigned int Number_Neurons_ = 12500; 
	
	const unsigned int Number_Neurons_Excitator = 10000;
	
	const unsigned int Number_Neurons_Inhibitor = 2500;
	
	const unsigned int Number_Connexion_excitator = 1000;
	
	const unsigned int Number_Connexion_inhibitor = 250;
	
	const unsigned int Number_Connexion_ = 1250;
	
	std::vector<std::vector<int>> connexions;  /*! vector<vector>> that represent the connexion between the neurons*/
	
	double Clock_ = 0.0; /*! Time of the programm */
	
	long Step_Clock_ = 0; /*! Step of the programm */
	
	long Step_End; 
	
	std::vector<Neuron*> neurons; /*! Vector of all the neurons */
	
	public : 
	/**
	 * @return 
	 * @param 
	 */
	 
	/*! Constructor */
	Cortex();
	
	/*! Destructor*/
	~Cortex(); 
	
	/*! Copy constructor */
	Cortex(Cortex const& other); 
	
	/** Neuron initialisation 
	 * @param : I ext is normally 0.0
	 * @param : Ji represents the inhibitor aspects of neurons
	 * */
	void initialise_neuron(long start, double Iext, double Ji);
	
	/** Update all neurons
	 * 	@param : ratio = Vthr/Vext = eta
	 * */
	void update_neuron(long Step_start, long Step_end, double ratio);
	
	/*! Write a file with all the membrane potential and the time*/
	void Save_to_file();
	
	/*! Write the time when spike occures in the terminal */
	void time_spike();
	
	/*! Initialise the clock */
	void setClock(double clock);
	
	/*! Delete neurones, Warning : neurons is a vector with pointeur */
	void Reset();
	
	/*! Initialise the start step */
	void setStepClock(long num);
	
	/*! Initialise the stop step */ 
	void setStepEnd(long num);
	
	/*! Add input in one neuron */
	void setNeuronInput(int i, double Input);
	
	/*! Give a random number with the same probability for each */
	int Random_Uniform(unsigned int start, unsigned int stop);
	
	/*! Initialise the connexions between the neurons */
	void Initialise_Connexions();
	
	/**
	 * Write a document to draw the plot
	 * @param : name of a document to have 4 ones
	 */
	void Document_Python(std::ofstream &doc);
	
};

#endif
