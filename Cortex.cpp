#include "Cortex.hpp"
#include <random>

Cortex::Cortex() {}

Cortex::~Cortex() {}

Cortex::Cortex(Cortex const& other)
: neurons(other.neurons) {};

void Cortex::initialise_neuron(long start, double Iext)
{
	/*for(size_t i(0); i < Number_Neurons_; ++i) 
	{ 
			if(i == 0) {
				neurons.push_back(new Neuron(Iext));
				neurons[i]->getTime_(start * dt);
				neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);	
			} else {
				neurons.push_back(new Neuron(0.0));
				neurons[i]->getTime_(start * dt);
				neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
			}
	}*/
	
	for(unsigned int i(0); i < Number_Neurons_; ++i) 
	{
		connexions.push_back({});
		for(unsigned int j(0); j < Number_Neurons_; ++j) 
		{
			connexions[i].push_back(0);
		}
	}
	
	for(size_t i(0); i < Number_Neurons_Excitator; ++i)
	{
		neurons.push_back(new Neuron(0.1));
		neurons[i]->getTime_(start * dt);
		neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
	}
	
	for(size_t i(Number_Neurons_Excitator); i < Number_Neurons_Inhibitor; ++i)
	{
		neurons.push_back(new Neuron(0.5));
		neurons[i]->getTime_(start * dt);
		neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
	}
	
}



void Cortex::update_neuron(long Step_start, long Step_end) 
{	/*std::cout << "hello" << std::endl;
	std::cout << "step start : " << Step_start << std::endl;
	std::cout << "Step_Clock_ : " << Step_Clock_ << std::endl;
	std::cout << "Step_end : " << Step_End << std::endl;*/
	if((Step_Clock_ >= Step_start) and (Step_Clock_ < Step_end)) {
		//std::cout << "If update_neuron" << std::endl;
		while(Step_Clock_ < Step_End) {
			for(size_t i(0); i < neurons.size(); ++i) {
				//std::cout << "Time stop" << std::endl;
				//std::cout << "Dans la boucle update_neuron" << std::endl;
				bool spikeneuro(neurons[i]->update(Step_Clock_));
				if(spikeneuro and (! connexions.empty())) {
					//std::cout << "if dans update_neuron" << std::endl;
					//neurons[i+1]->sumInput(J);
					for(size_t j(0); j < Number_Neurons_; ++j) 
					{
						size_t m = neurons[j]->getRingBuffer().size();
						//std::cout << "taille de Ring_Buffer_ : " << m << std::endl;
						//int num = neurons[i+1]->getStep();
						const auto t_out = (Step_Clock_ % (m-1));
						int a = connexions[i][j];
						assert(t_out < m);
						neurons[j]->setRingBuffer(t_out,a);
					}
				}
			}
			++Step_Clock_ ;
			//Clock_ = Step_Clock_ * dt + t_start;
			//std::cout << "Step_clock : " << Step_Clock_ << std::endl;
		}
	//std::cout << "Clock: " << Clock_ << std::endl;
	}
}

void Cortex::load_from_file() {
	std::ofstream fichier("Neuron.txt");
	for(size_t i(0); i < neurons.size(); ++i) {
	if(!fichier.fail()) {
					fichier << "Time : " << Clock_ << std::endl;
					fichier << "Membrane potential : " << neurons[i]->getMembranePotential() << std::endl;
				} else {
					std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
				}	
	fichier.close();
	
	}
}

void Cortex::time_spike() 
{
	std::ofstream fichier("Time_Spike.txt");
	if(!fichier.fail()) {
		for(size_t i(0); i < neurons.size(); ++i) {
			std::cout << "Time when the spikes occured for neuron: " << i << std::endl;
			neurons[i]->getTimeSpike();
		}
	}
	fichier.close();
}

void Cortex::setClock(double clock)
{
	Clock_  = clock;
	
}

void Cortex::Reset()
{
	for(auto& neuron : neurons)
	{
		delete neuron;
		neuron = nullptr;
	}
	
	neurons.clear();
}

void Cortex::setStepClock(long num)
{
	Step_Clock_ = num;
}

void Cortex::setStepEnd(long num)
{
	Step_End = num;
}

void Cortex::setNeuronInput(int i, double Input)
{
	neurons[i]->set_i_ext(Input);
}

int Cortex::Random_Uniform(int size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, size - 1);
	
	return dis(gen);
}

void Cortex::Initialise_Connexions()
{
	for(unsigned int i(0); i < Number_Neurons_Excitator; ++i) 
	{
		for(unsigned int k(0); k < Number_Connexion_excitator; ++k) 
		{
			int ran = Random_Uniform(Number_Neurons_);
			connexions[i][ran] += 1;
		}
	}
	
	for(unsigned int i(Number_Neurons_Excitator); i < Number_Neurons_; ++i) 
	{
		for(unsigned int k(0); k < Number_Connexion_inhibitor; ++k) 
		{
			int ran = Random_Uniform(Number_Neurons_);
			connexions[i][ran] += 1;
		}
	}
}
