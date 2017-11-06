#ifndef Neuron_HPP
#define Neuron_HPP
#include <iostream>
#include <vector>
#include "Const.hpp"
#include <cmath>

#ifdef TEST
#include <gtest/gtest_prod.h>
#endif

class Neuron
{
	private :
	
		#ifdef TEST
	FRIEND_TEST (oneNeuron, calculate_potential);
	FRIEND_TEST (oneNeuron, time_spikes);
	FRIEND_TEST(twoNeuron, Connexion_with_oneSpike);
	FRIEND_TEST(twoNeurons, Connexion_with_twoSpikes);
		#endif  
	
	/*! Const : */
	const double Jext = 0.1;
	const double tau = 20.0; //tau = resistance * capacity
	const double resistance = 20.0; //= tau / capacity; //résistance du neurone
	const long potential_seuil = 20.0; //seuil en dessous duquel pas de spike
	const double capacity = 1.0; //capacité du neurone
	const double time_refractaire = 2.0; //temps de réfractation entre deux spikes
	const double t_delay = 1.5; //time to delay
	const double cte1 = exp(-dt / tau);
	const double cte2 = resistance * (1-cte1);
	
	unsigned int spike; /*! Number of spikes */
	double potential; /*! Membrane Potential */
	double n_J = 0.0; /*! Number of J not use now */
	double time_; /*! Time from the start of the experience */ 
	long step = 0; /*! Number of steps */ 
	std::vector<double> Ring_Buffer_; /*! Ring buffer to delay the moment */
	long step_refractory = 0;
	double Iext = 0.0;
	double J; /*! Depend if the neuron is excitatory or inhibitory */
	std::vector<double> time_spike; /*! Vector where all the spikes are noted */
	std::vector<int> outgoing_;
	
	public:
	
	/*! Constructor */
	Neuron(double j); 
	
	/*! Destructor */
	~Neuron();
	
	/*! Copy constructor */
	Neuron(Neuron const& other); 
	
	/*! Calcul the membrane potential at time t + dt */
	bool update(long step_clock_, double pois);
	
	/*! Sum J (not use now) */
	void sumInput(double J);
	
	/** Modify Ring Buffer
	 * @param : i = numero of the case in the tab
	 * */
	void setRingBuffer(size_t i, double j);
	
	/*! Resize the ring buffer*/
	void resizeRingBuffer(int i);
	
	/*! Getteur : */
	std::vector<double> getRingBuffer();
	
	double getMembranePotential() const; //Renvoie la valeur du potentiel membranaire
	
	double getNumberSpike() const; //Renvoie le nombre de spike
	
	void getTimeSpike() const; //Affiche les moments où ont lieu les spikes
	
	void getTime_(double t); //Renvoie le temps du neurone
	
	double getDelay(); //Renvoie le delai entre deux dt

	int getStep();
	
	long getStepRefractory();
	
	std::vector<double> getTimeSpikeVector();
	
	std::vector<int> getOutgoing();
	
	double getJ();
	
	/*! Setteur : */
	void set_i_ext(double I);
	
	void setPotentialPoisson(int n);
	
	void setOutgoing(int neu);
};

#endif

//cin >> texte;
