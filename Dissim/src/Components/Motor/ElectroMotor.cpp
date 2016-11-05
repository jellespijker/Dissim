#include "Components/Motor/ElectroMotor.h"

namespace dissim {
namespace Components {

ElectroMotor::ElectroMotor() {
    DissimType::Dissim_ptr Power( new DissimType );
    Power->Dimension = "W";
    Power->Symbol = "P";

    DissimType::Dissim_ptr Omega( new DissimType );
    Omega->Dimension = "rad/s";
    Omega->Symbol = "omega";

    DissimType::Dissim_ptr Torque = OutputPorts[0];
    Torque->Dimension = "N/m";
    Torque->Symbol = "T";

    InputPorts.push_back(Power);;
    InputPorts.push_back(Omega);

    Block_ptr DivBlock( new BasicOperationBlock ) ;
    DivBlock->Name = "DivBlock";
    DivBlock->push_back( Power, BasicOperationBlock::Multplication  );
    DivBlock->push_back( Omega, BasicOperationBlock::Division );
    DivBlock->OutputPorts[0]->Description = "Torque optimal";
    DivBlock->OutputPorts[0]->Dimension = "N/m";
    DivBlock->OutputPorts[0]->Symbol = "T_opt";

    Block_ptr SatBlock( new Saturation ) ;
    SatBlock->Name = "T";
    SatBlock->push_back(DivBlock->OutputPort, 0);
    SatBlock->RescaleInputsMatrix(1, 1);
    SatBlock->OutputPorts[0] = Torque;
    SatBlock->OutputPort = Torque;

    SystemBlocks.push_back( DivBlock );
    SystemBlocks.push_back( SatBlock );
}

ElectroMotor::~ElectroMotor() {

}



}
}
