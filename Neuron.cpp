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
	--step_refractory;
	
	std::cout << "Dans Neuron::update " << std::endl;
	
	if(potential > potential_seuil) {
		//last_spike_ = (dt * step + t_start);
		step_refractory = time_refractaire / dt;
		time_spike.push_back(dt * step + t_start); //ajoute au tableau le moment où le spike à lieu
		time_refractaire = 2.0;
		potential = 0.0;
		++spike;
		return true;
	}
	
	/*if ( (dt * step + t_start) == ( last_spike_ + t_delay)) {
		
		return true;
	}*/
	
	
	if(step_refractory > 0) {
		potential = 0.0;
	} else {
		potential = (cte1 * potential + resistance * Iext * (1 - cte1) + Ring_Buffer_[step % Ring_Buffer_.size() +1 ]); //+ n_J);
		//n_J = 0.0;
		Ring_Buffer_[step % Ring_Buffer_.size() +1] = 0.0;
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

double Neuron::getDelay()
{
	return t_delay;
}

std::vector<double> Neuron::getRingBuffer()
{
	return Ring_Buffer_;
}

void Neuron::setRingBuffer(size_t i, double J)
{
	
	Ring_Buffer_[i] += J;
}

void Neuron::resizeRingBuffer(int i)
{
	Ring_Buffer_.resize(i);
}

int Neuron::getStep()
{
	return step;
}

