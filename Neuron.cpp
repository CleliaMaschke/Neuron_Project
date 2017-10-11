#include "Neuron.hpp"
#include <cmath>

Neuron::Neuron()
: spike(0), potential(0.0) {}

Neuron::~Neuron() {}

Neuron::Neuron(Neuron const& other)
: spike(other.spike), potential(other.potential) {}



bool Neuron::update(double dt, double Iext, double t_start)
{
	double cte1 = exp(-dt / tau);
	time_refractaire -= dt;
	
	if(potential > potential_seuil) {
		time_spike.push_back(dt * step + t_start); //ajoute au tableau le moment où le spike à lieu
		time_refractaire = 2.0;
		potential = 0.0;
		++spike;
		return true;
	}
	
	if(time_refractaire > 0) {
		potential = 0.0;
	} else {
		potential = (cte1 * potential + resistance * Iext * (1 - cte1) + n_J);
		n_J = 0.0;
	}
	
	++step;
	return false;
}

double Neuron::getMembranePotential() const
{
	return potential;
}

double Neuron::getNumberSpike() const
{
	return spike;
}

void Neuron::getTimeSpike() const
{
	for(size_t i(0); i < time_spike.size(); ++i){
		std::cout << time_spike[i] << std::endl;
	}
}

void Neuron::getTime_(double t)
{
	time_ = t;
}

void Neuron::sumInput(double J)
{
	n_J += J;
}



