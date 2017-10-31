#include "Cortex.hpp"
#include <random>
#include <map>

Cortex::Cortex() {}

Cortex::~Cortex() {}

Cortex::Cortex(Cortex const& other)
: neurons(other.neurons) {};

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
	
	std::cout << "Neurons.size() = " << neurons.size() << std::endl;
	
}



void Cortex::update_neuron(long Step_start, long Step_end, int ratio) 
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
				if(neurons[i]->getStepRefractory() <= 0) {
					neurons[i]->setPotentialPoisson(ratio);
				}
				if(spikeneuro and (! connexions.empty())) {
					//std::cout << "if dans update_neuron" << std::endl;
					//neurons[i+1]->sumInput(J);
					for(size_t j(0); j < Number_Connexion_; ++j) 
					{
						size_t m = neurons[connexions[i][j]]->getRingBuffer().size();
						//std::cout << "taille de Ring_Buffer_ : " << m << std::endl;
						//int num = neurons[i+1]->getStep();
						const auto t_out = (Step_Clock_ % (m-1));
						assert(t_out < m);
						neurons[connexions[i][j]]->setRingBuffer(t_out);
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

int Cortex::Random_Uniform(unsigned int start, unsigned int stop)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(start, stop - 1);
	
	return dis(gen);
}

void Cortex::Initialise_Connexions()
{
	for(unsigned int i(0); i < Number_Neurons_; ++i) {
		connexions.push_back({});
		for(unsigned int j(0); j < Number_Connexion_excitator; ++j) {
			int ran = Random_Uniform(0, Number_Neurons_Excitator);
			connexions[i].push_back(ran);
		}
		
		for (unsigned int k(0); k < Number_Connexion_inhibitor; ++k)
		{
			int ran = Random_Uniform(Number_Neurons_Excitator, Number_Neurons_);
			connexions[i].push_back(ran);
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
