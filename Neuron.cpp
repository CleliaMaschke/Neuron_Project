#include "Neuron.hpp"
#include <cmath>

Neuron::Neuron()
: spike(0), potential(0.0) {}

Neuron::~Neuron() {}

Neuron::Neuron(Neuron const& other)
: spike(other.spike), potential(other.potential) {}

void Neuron::update(double dt, double Iext)
{
	double cte1 = exp(-dt / tau);
	time_ += dt;
	time_refractaire -= dt;
	
	if(time_refractaire > 0) {
		potential = 0.0;
	} else if(potential > potential_seuil) {
		time_spike.push_back(time_); //ajoute au tableau le moment où le spike à lieu
		time_refractaire = 2;
		potential = 0.0;
		++spike;
	}
	if(potential < potential_seuil and time_refractaire <= 0) {
		potential = (cte1 * potential + resistance * Iext * (1 - cte1));
	}
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





