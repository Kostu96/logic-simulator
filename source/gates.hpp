#pragma once
#include "component.hpp"

class BufferGate :
    public Component
{
public:
    BufferGate() :
        Component{ 1, 1 } {}

    std::vector<Bit> update(std::vector<Bit> inputs) override
    {
        assert(inputs.size() == getInputsCount());
        return inputs;
    }
};

class NotGate :
    public Component
{
public:
    NotGate() :
        Component{ 1, 1 } {}

    std::vector<Bit> update(std::vector<Bit> inputs) override
    {
        assert(inputs.size() == getInputsCount());

        switch (inputs[0]) {
        case Bit::Undefined: return { Bit::Undefined };
        case Bit::High:      return { Bit::Low };
        case Bit::Low:       return { Bit::High };
        }
    }
};

class NandGate :
    public Component
{
public:
    NandGate(size_t inputs) :
        Component{ inputs, 1 } {}

    std::vector<Bit> update(std::vector<Bit> inputs) override
    {
        assert(inputs.size() == getInputsCount());

        Bit ret = Bit::Low;
        for (const auto& input : inputs)
            switch (input) {
            case Bit::Low: return { Bit::High };
            case Bit::Undefined: ret = Bit::Undefined;
            }

        return { ret };
    }
};
