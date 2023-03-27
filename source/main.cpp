#include "gates.hpp"

class Circuit :
    public Component
{
public:
    Circuit(size_t inputs, size_t outputs) :
        Component{ outputs, inputs }
    {
        m_components.push_back(this);
    }

    std::vector<Bit> update(std::vector<Bit> inputs) override
    {
        // propagate input
        m_outputs = inputs;
        propagate(0);
        
        // update components
        for (size_t id = 1; id < m_components.size(); id++)
            m_components[id]->getOutputs() = m_components[id]->update(m_components[id]->getInputs());

        // propagate signals
        for (size_t id = 1; id < m_components.size(); id++)
            propagate(id);

        return m_inputs;
    }

    void propagate(size_t componentID)
    {
        size_t outID = 0;
        for (auto& index : m_connections[componentID]) {
            if (index.componentID == 0) __debugbreak();
            auto& inputs = m_components[index.componentID]->getInputs();
            auto& outputs = m_components[componentID]->getOutputs();
            inputs[index.inputID] = outputs[outID++];
        }
    }

    size_t addComponent(Component* component)
    {
        m_components.push_back(component);
        return m_components.size() - 1;
    }
private:
    std::vector<Component*> m_components;
};

int main()
{
    // test NAND gate
    NandGate nandGate{ 2 };
    std::cout << "NAND Gate:\n";
    std::cout << " A B | Y\n";
    std::cout << " L L | " << nandGate.update({ Bit::Low, Bit::Low })[0] << '\n';
    std::cout << " L H | " << nandGate.update({ Bit::Low, Bit::High })[0] << '\n';
    std::cout << " H L | " << nandGate.update({ Bit::High, Bit::Low })[0] << '\n';
    std::cout << " H H | " << nandGate.update({ Bit::High, Bit::High })[0] << '\n';
    
    std::cout << std::endl;

    // test OR gate
    Circuit ORGate{ 2, 1 };

    NotGate notA;
    NotGate notB;
    NandGate nand{ 2 };

    size_t notAID = ORGate.addComponent(&notA);
    size_t notBID = ORGate.addComponent(&notB);
    size_t nandID = ORGate.addComponent(&nand);

    ORGate.addConnection(0, { notAID, 0 });
    ORGate.addConnection(1, { notBID, 0 });
    notA.addConnection(0, { nandID, 0 });
    notB.addConnection(0, { nandID, 1 });
    nand.addConnection(0, { 0, 0 });

    std::cout << "OR Gate\n";
    std::cout << " A B | Y\n";
    std::cout << " L L | " << ORGate.update({ Bit::Low, Bit::Low })[0] << '\n';
    std::cout << " L H | " << ORGate.update({ Bit::Low, Bit::High })[0] << '\n';
    std::cout << " H L | " << ORGate.update({ Bit::High, Bit::Low })[0] << '\n';
    std::cout << " H H | " << ORGate.update({ Bit::High, Bit::High })[0] << '\n';

    return 0;
}
