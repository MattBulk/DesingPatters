#ifndef SOMENEURONS_H
#define SOMENEURONS_H

#include <vector>

template <typename Self>
class SomeNeurons
{
public:
    class Neuron : public SomeNeurons<Neuron>
    {
    public:
        std::vector<Neuron *> in, out;
        unsigned int id;

        Neuron()
        {
            static int id = 1;
            this->id = id++;
        }
        ~Neuron() {}

        Neuron *begin() override
        {
            return this;
        }
        Neuron *end() override
        {
            return this + 1;
        }
    };
    
    class NeuronLayer : std::vector<Neuron>
    {
        NeuronLayer(int count) {
            while (count --> 0)
            {
                emplace_back(Neuron{});
            }
            
        }
    };
    
    
    template <typename T>
    void connect_to(T &other)
    {
        for (Neuron &from : *static_cast<Self *>(this))
        { // we need to catch Self not SomeNeurons, so that the cast.
            for (Neuron &to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }

    virtual Neuron *begin() = 0;
    virtual Neuron *end() = 0;
};

#endif