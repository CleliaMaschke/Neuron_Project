#include "Neuron.hpp"
#include <cmath>
#include <random>

Neuron::Neuron(double j)
: spike(0), potential(0.0), J(j)
{
	
}

Neuron::~Neuron() {}

Neuron::Neuron(Neuron const& other)
: spike(other.spike), potential(other.potential) {}


bool Neuron::update(long step_clock_)
{
	--step_refractory;
	
	//std::cout << "Dans Neuron::update " << std::endl;
	
	if(potential > potential_seuil) {
		time_spike.push_back(step_clock_ * dt); //ajoute au tableau le moment où le spike à lieu
		potential = 0.0;
		step_refractory = time_refractaire /dt; //ajoute 2 step car 1 step = 0.1 et le temps réfracatire = 0.2
		++spike;
		return true;
	}
	
	if(step_refractory > 0) {
		potential = 0.0;
	} else {
		//double pois = Random_Poisson();
		potential = (cte1 * potential + resistance * Iext * (1 - cte1) + Ring_Buffer_[step % Ring_Buffer_.size() +1] ); //+ pois * Jext
		Ring_Buffer_[step % Ring_Buffer_.size() +1] = 0.0;
		//std::cout << "Poisson = " << pois << std::endl;
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

void Neuron::setRingBuffer(size_t i, int a)
{
	
	Ring_Buffer_[i] += a * J;
}

void Neuron::resizeRingBuffer(int i)
{
	Ring_Buffer_.resize(i);
}

int Neuron::getStep()
{
	return step;
}

void Neuron::set_i_ext(double I)
{
	Iext = I;
}

double Neuron::Random_Poisson()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	// if an event occurs 0.02 spikes/connection x ms
	std::poisson_distribution<> d(2);
	
	//std::cout << "Poisson : " << d(gen) << std::endl;
	
	return d(gen);
}

long Neuron::getStepRefractory()
{
	return step_refractory;
}

void Neuron::setPotentialPoisson()
{
	potential += Random_Poisson() * Jext;
}
