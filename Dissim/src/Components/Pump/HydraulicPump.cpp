#include "Components/Pump/HydraulicPump.h"
#include "Components/Math/K_HP.h"
#include "Components/Math/tau_friction.h"

namespace dissim {
namespace Components {

HydraulicPump::HydraulicPump() {
    Block_ptr k_hp(new K_HP(false));
    SystemBlocks.push_back(k_hp);
    reRouteInput(k_hp);

    Block_ptr tau_fr(new tau_friction);
    SystemBlocks.push_back(tau_fr);
    reRouteInput(tau_fr);

    InputPorts.push_back(DissimType::Dissim_ptr( new DissimType("v_f", "m * s^-1", "Speed of the fluid")));
    InputPorts.push_back(DissimType::Dissim_ptr( new DissimType("A_p", "m^2", "Cross section of the pipe")));
    InputPorts.push_back(DissimType::Dissim_ptr( new DissimType("D", "cm^3", "the Displacement parameter.")));

    Block_ptr a(new BasicOperationBlock("a"));
    a->push_back(getInputPort("v_f"), BasicOperationBlock::Multplication);
    a->push_back(getInputPort("A_p"), BasicOperationBlock::Multplication);
    SystemBlocks.push_back(a);

    Block_ptr b(new BasicOperationBlock("b"));
    b->push_back(getInputPort("D"), BasicOperationBlock::Multplication);
    b->push_back(getInputPort("omega"), BasicOperationBlock::Multplication);
    SystemBlocks.push_back(b);

    Block_ptr c(new BasicOperationBlock("c"));
    c->push_back(a->OutputPort, BasicOperationBlock::Subtraction);
    c->push_back(b->OutputPort, BasicOperationBlock::Addition);
    SystemBlocks.push_back(c);

    Block_ptr DeltaP(new BasicOperationBlock("DeltaP"));
    DeltaP->push_back(c->OutputPort, BasicOperationBlock::Multplication);
    DeltaP->push_back(k_hp->OutputPort, BasicOperationBlock::Division);
    OutputPorts[0] = DeltaP->OutputPort;
    OutputPorts[0]->Description = "the pressure drop from inlet to outlet.";
    OutputPorts[0]->Symbol = "DeltaP";
    OutputPorts[0]->Dimension = "Pa";
    SystemBlocks.push_back(DeltaP);

    Block_ptr tau_id(new BasicOperationBlock("tau_id"));
    tau_id->push_back(getInputPort("D"), BasicOperationBlock::Multplication);
    tau_id->push_back(DeltaP->OutputPort, BasicOperationBlock::Multplication);
    SystemBlocks.push_back(tau_id);

    Block_ptr tau(new BasicOperationBlock("tau"));
    tau->push_back(tau_id->OutputPort, BasicOperationBlock::Addition);
    tau->push_back(tau_fr->OutputPort, BasicOperationBlock::Addition);
    OutputPorts.push_back(tau->OutputPort);
    OutputPorts[1]->Symbol = "tau";
    OutputPorts[1]->Dimension = "N * m";
    OutputPorts[1]->Description = "the net torque.";
    SystemBlocks.push_back(tau);

}

HydraulicPump::~HydraulicPump() {

}
}
}
