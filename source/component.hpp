#pragma once
#include "bit.hpp"

#include <cassert>
#include <vector>

struct Index
{
    size_t componentID;
    size_t inputID;
};

class Component
{
public:
    Component(size_t inputs, size_t outputs) :
        m_inputsCount{ inputs },
        m_outputsCount{ outputs },
        m_connections{ outputs }
    {
    }

    virtual std::vector<Bit> update(std::vector<Bit> inputs) = 0;

    void addConnection(size_t outputID, Index index)
    {
        assert(outputID < getOutputsCount());

        m_connections[outputID].push_back(index);
    }

    size_t getInputsCount() const { return m_inputsCount; }
    size_t getOutputsCount() const { return m_outputsCount; }
    std::vector<Bit>& getInputs() { return m_inputs; };
    std::vector<Bit>& getOutputs() { return m_outputs; };
protected:
    size_t m_inputsCount;
    size_t m_outputsCount;
    std::vector<Bit> m_inputs;
    std::vector<Bit> m_outputs;
    std::vector<std::vector<Index>> m_connections;
};
