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


bool Neuron::update(long step_clock_, double pois)
{	
	//std::cout << "Step refractaire -- = " << step_refractory << std::endl;
	int position = step % Ring_Buffer_.size();
	//std::cout << "Dans Neuron::update " << std::endl;
	if(step_refractory > 0) {
		potential = 0.0;
		--step_refractory;
		return false;
	} else {
		if(potential >= potential_seuil) {
			time_spike.push_back(step_clock_ * dt); //ajoute au tableau le moment où le spike à lieu
			potential = 0.0;
			step_refractory = time_refractaire / dt; //ajoute 2 step car 1 step = 0.1 et le temps réfracatire = 0.2
			//std::cout << "Step refractaire dans else = " << step_refractory << std::endl;
			++spike;
			return true;
		} else {
			//double pois = Random_Poisson();
			potential = (cte1 * potential + Iext * cte2 + Ring_Buffer_[position])+ pois * Jext; //
			
			//std::cout << "Potential = " << potential << std::endl;
			//std::cout << "Poisson = " << pois << std::endl;
		}
	}
	Ring_Buffer_[position] = 0.0;
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

void Neuron::setRingBuffer(size_t i, double j)
{
	
	Ring_Buffer_[i] += j;
	//std::cout << "J = " << J << std::endl;
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

long Neuron::getStepRefractory()
{
	return step_refractory;
}

std::vector<double> Neuron::getTimeSpikeVector()
{
	return time_spike;
}

void Neuron::setOutgoing(int neu)
{
	outgoing_.push_back(neu);
}

std::vector<int> Neuron::getOutgoing()
{
	return outgoing_;
}

double Neuron::getJ()
{
	return J;
}
