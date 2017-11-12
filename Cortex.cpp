#include "Cortex.hpp"
#include <random>
#include <map>

Cortex::Cortex() {}

Cortex::~Cortex() {}

Cortex::Cortex(Cortex const& other)
: neurons(other.neurons) {}

void Cortex::initialise_neuron(long start, double Iext, double Ji)
{
	
	for(size_t i(0); i < Number_Neurons_Excitator; ++i)
	{
		neurons.push_back(new Neuron(0.1));
		neurons[i]->getTime_(start * dt);
		neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
	}

	for(size_t i(Number_Neurons_Excitator); i < Number_Neurons_; ++i)
	{
		neurons.push_back(new Neuron(Ji));
		neurons[i]->getTime_(start * dt);
		neurons[i]->resizeRingBuffer(neurons[i]->getDelay() / dt + 1);
	}
	
}



void Cortex::update_neuron(long Step_start, long Step_end, double ratio) 
{	
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution<> d(ratio);

	if((Step_Clock_ >= Step_start) and (Step_Clock_ < Step_end)) {
	
		size_t m = neurons[0]->getRingBuffer().size(); // all neurons have the same ring buffer size
		long D = neurons[0]->getDelay() / 0.1; //all neurons have the same delay 
	
		while(Step_Clock_ < Step_End) {
			const auto t_out = ((Step_Clock_ + D) % m);
			assert(t_out < m);
			for(size_t i(0); i < neurons.size(); ++i) {
	
				if(neurons[i]->update(Step_Clock_, d(gen))) {
				
					for(auto element : neurons[i]->getOutgoing()) 
					{
						neurons[element]->setRingBuffer(t_out, neurons[i]->getJ());
					}
				}
			}
			++Step_Clock_ ;
		}
	}
}

void Cortex::Save_to_file() 
{ 
	std::ofstream fichier("Neuron.txt");
	if(!fichier.fail()) {
		for(size_t i(0); i < neurons.size(); ++i) {
			fichier << "Time : " << Clock_ << std::endl;
			fichier << "Membrane potential : " << neurons[i]->getMembranePotential() << std::endl;
		} 
		
	} else {
			std::cout << "Problem with Neuron.txt, save impossible" << std::endl;
		}
	fichier.close();
}

void Cortex::time_spike() 
{
	for(size_t i(0); i < neurons.size(); ++i) {
			std::cout << "Time when the spikes occured for neuron: " << i << std::endl;
			neurons[i]->getTimeSpike();
		}
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

void Cortex::Initialise_Connexions()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, Number_Neurons_Excitator - 1);
	static std::uniform_int_distribution<> dis_i(Number_Neurons_Excitator, Number_Neurons_ - 1);
		
		for(unsigned int i(0); i < Number_Neurons_; ++i) {
			
			for(unsigned int j(0); j < Number_Connexion_excitator; ++j) {
				neurons[dis(gen)]-> setOutgoing(i);
			}
		
		for (unsigned int k(0); k < Number_Connexion_inhibitor; ++k)
			{
				neurons[dis_i(gen)]-> setOutgoing(i);
			}
	}
}

void Cortex::Document_Python(std::ofstream &doc) 
{
	if(!doc.fail()) {
		for(size_t i(0); i < neurons.size(); ++i) {
			std::vector<double> tab = neurons[i]->getTimeSpikeVector();
			for(size_t j(0); j < tab.size(); ++j) {
				doc << tab[j] << "\t" << i << "\n";
			}
		}
	}
}


long Cortex::getSizeNeurons()
{
	return neurons.size();
}

