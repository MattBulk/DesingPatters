#ifndef SOMENEURONS_H
#define SOMENEURONS_H

#include <vector>

// used Self to be able to solve class declaration
template <typename Self>
class SomeNeurons
{
public:
    template <typename T>
    void connect_to(T &other)
    {
        for (Self &from : *static_cast<Self *>(this))
        { // we need to catch Self not SomeNeurons, so that the cast.
            print("Connect From is: ", from.id);
            for (Self &to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
                print("connect to id: ", to.id);
            }
        }
    }

    virtual Self *begin() = 0;

    virtual Self *end() = 0;
};

class Neuron : public SomeNeurons<Neuron>
{
public:
    // friend class SomeNeurons;

    std::vector<Neuron *> in, out;
    unsigned int id;

    Neuron()
    {
        static int id = 1;
        this->id = id++;
        print("Neuron id: ", this->id);
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

// I cannot 
class NeuronLayer : public Neuron
{
public:
    std::vector<Neuron> neurons;
    NeuronLayer(int count)
    {
        while (count-- > 0)
        {
            Neuron n{};
            neurons.emplace_back(n);
            print("NeuronLayer append neuron id: ", n.id);
        }
    }
};

#endif