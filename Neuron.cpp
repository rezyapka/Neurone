// Neuron.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

class Neuron
{ 
	struct Edge
	{
		Neuron* neuron;
		double weight;
	};
protected:
	vector<Edge>neurons;
public:
	void addNeuron (double weight, Neuron *neuron)
	{
		Edge IN_Neurons; 
		IN_Neurons.neuron = neuron;
		IN_Neurons.weight = weight;
		neurons.push_back(IN_Neurons);
	}


	float GetExit()
	{
		return function_OUT();
	}
protected:

	float function_sum()
	{
		float sum = 0;
		for (auto the_iterator = neurons.begin(); the_iterator != neurons.end(); the_iterator++)
		{
			sum += the_iterator->weight * (the_iterator->neuron->GetExit()); 

		}
		return sum;
	}

	virtual float function_OUT() = 0;


};
class entry_neurone: public Neuron
{
	float value;
public:
	void setValue(float v)
	{
		value = v;
	}
protected:
	virtual float function_OUT()
	{
		return value;
	}
};
class hidden_neurone: public Neuron
{
protected:
	float function_OUT()
	{
		//return (1.0/(1.0+exp(-function_sum())));
		float s=function_sum();
		if (s<0)
			return 0;
		else return 1;
	}
};

class constant_neurone:public Neuron
{
protected:
	virtual float function_OUT()
	{
		return 1;
	}	
};
int _tmain(int argc, _TCHAR* argv[])
{
	float x1 = 1;
	float x2 = 1;
	//cout<<"Write value of neurons"<<endl;
	//cin>>x1;
	//cin>>x2;
	entry_neurone x;
	entry_neurone y;
	constant_neurone z;
	x.setValue(x1);
	y.setValue(x2);
	hidden_neurone x_1;
	hidden_neurone y_1;
	constant_neurone z_1;

	x_1.addNeuron(-1,&x);
	x_1.addNeuron(-1,&y);
	x_1.addNeuron(1.5,&z);

	y_1.addNeuron(-1,&x);
	y_1.addNeuron(-1,&y);
	y_1.addNeuron(0.5,&z);

	hidden_neurone k;
	k.addNeuron(1,&x_1);
	k.addNeuron(-1,&y_1);
	k.addNeuron(-0.5,&z_1);

	cout<<k.GetExit()<<endl;
		return 0;
}

