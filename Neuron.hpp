#ifndef Neuron_HPP
#define Neuron_HPP
#include <iostream>
#include <vector>

#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

class Neuron
{
	private :
	
		#ifdef TEST
	FRIEND_TEST (Neuron_Test, calculate_potential)
		
		#endif
	
	unsigned int spike; //Number of spikes
	double potential; //potential
	std::vector<double> time_spike; //tableau qui note le temps où à lieu le spike
	const double capacity = 1.0; //capacité du neurone
	const double tau = 20.0; //tau = resistance * capacity
	const double resistance = 20.0; //= tau / capacity; //résistance du neurone 
	long potential_seuil = 20.0; //seuil en dessous duquel pas de spike
	double time_refractaire = 0.0; //temps de réfractation entre deux spikes
	double time_; //temps depuit le début de l'expérience
	const double J = 0.1; //[mV]
	double n_J = 0.0; //number of input of other neuron 
	double t_delay = 1.5; //time to delay 
	int step = 0; //number of step dt 
	double last_spike_ = 0.0;
	
	
	public:
	
	Neuron(); //constructeur 
	
	~Neuron(); //Destructeur 
	
	Neuron(Neuron const& other); //constructreur de copie
	
	bool update(double dt, double Iext, double t_start); //calcule le potentiel au temps t+dt
	
	double getMembranePotential() const; //Renvoie la valeur du potentiel membranaire
	
	double getNumberSpike() const; //Renvoie le nombre de spike
	
	void getTimeSpike() const; //Affiche les moments où ont lieu les spikes
	
	void getTime_(double t);
	
	void sumInput(double J);
	
};

#endif

//cin >> texte;
