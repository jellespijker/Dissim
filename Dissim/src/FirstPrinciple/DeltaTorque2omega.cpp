#include "FirstPrinciple/DeltaTorque2omega.h"

namespace dissim {
namespace FirstPrinciple {

DeltaTorque2omega::DeltaTorque2omega() {
    InputPorts.push_back( DissimType::Dissim_ptr ( new DissimType( "T_d", "N/m", "Torque delivered" ) ) );
    InputPorts.push_back( DissimType::Dissim_ptr ( new DissimType( "T_n", "N/m", "Torque needed" ) ) );
    InputPorts.push_back( DissimType::Dissim_ptr ( new DissimType("J", "kg*m^2", "Moment of inertia") ) );

    Block_ptr J_tot( new BasicOperationBlock("J_tot") );
    J_tot->push_back(getInputPort("J"), BasicOperationBlock::Addition);
    J_tot->OutputPort->Description = "Total moment of inertia";
    J_tot->OutputPort->Dimension = "kg*m^2";
    J_tot->OutputPort->Symbol = "J_tot";
    SystemBlocks.push_back(J_tot);

    Block_ptr dT( new BasicOperationBlock("dT") );
    dT->push_back(getInputPort("T_d"), BasicOperationBlock::Addition);
    dT->push_back(getInputPort("T_n"), BasicOperationBlock::Subtraction);
    dT->OutputPort->Description = "Delta Torque";
    dT->OutputPort->Dimension = "N/m";
    dT->OutputPort->Symbol = "dT";
    SystemBlocks.push_back(dT);

    Block_ptr alpha( new BasicOperationBlock("alpha") );
    alpha->push_back(dT->OutputPort, BasicOperationBlock::Multplication);
    alpha->push_back(J_tot->OutputPort, BasicOperationBlock::Division);
    alpha->OutputPort->Description = "Angular acceleration";
    alpha->OutputPort->Dimension = "rad/s^2";
    alpha->OutputPort->Symbol = "alpha";
    SystemBlocks.push_back(alpha);

    Block_ptr omega( new Integrator("omega") );
    omega->push_back(alpha->OutputPort, BasicOperationBlock::Integrate);
    omega->OutputPort = OutputPort;
    omega->OutputPorts[0] = OutputPort;
    omega->OutputPort->Description = "Angular speed";
    omega->OutputPort->Dimension = "rad/s";
    omega->OutputPort->Symbol = "omega";
    SystemBlocks.push_back(omega);
}

DeltaTorque2omega::DeltaTorque2omega(std::string name) {
    this->Name = name;
    DeltaTorque2omega();
}

DeltaTorque2omega::~DeltaTorque2omega() {

}

}
}
