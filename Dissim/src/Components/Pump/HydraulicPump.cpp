#include "Components/Pump/HydraulicPump.h"

namespace dissim {
namespace Components {

HydraulicPump::HydraulicPump() {

    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("v", "m/s", "Velocity of the fluid") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("omega", "rad/s", "Pump angular velocity") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("omega_nom", "rad/s", "Pump nominal angular velocity") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("rho_nom", "k/m^3", "Nominal specific weight of the fluid") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("rho", "k/m^3", "Specific weight of the fluid") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("vis_nom", "m^2/s", "Nominal fluid kinematic viscosity" ) ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("vis", "m^2/s", "Fluid kinematic viscosity" ) ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("A", "m^2", "Cross-section Pipe") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("P_nom", "Pa", "Pump nominal pressure") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("Vg_max", "cm^3", "Pump max displacement") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("Ethafluid", "-", "Pump volumetric efficiency") ) );
    InputPorts.push_back( DissimType::Dissim_ptr( new DissimType("EthaMech", "-", "Pump mechanical efficiency") ) );

    Block_ptr Inv_etha( new BasicOperationBlock("Inv_etha") );
    Inv_etha->push_back(BasicOperationBlock::Addition);
    Inv_etha->InputPorts[0]->Dimension = "-";
    Inv_etha->InputPorts[0]->Symbol = "Optimum_etha";
    Inv_etha->InputPorts[0]->Value << 1;
    Inv_etha->push_back(getInputPort("Ethafluid"), BasicOperationBlock::Subtraction);
    Inv_etha->OutputPort->Description = "Inverse etha fluid";
    Inv_etha->OutputPort->Dimension = "-";
    Inv_etha->OutputPort->Symbol = "Ethafluid_inv";
    SystemBlocks.push_back(Inv_etha);

    Block_ptr K_HP( new BasicOperationBlock("K_HP") );
    K_HP->push_back(getInputPort("Vg_max"), BasicOperationBlock::Multplication);
    K_HP->push_back(getInputPort("omega_nom"), BasicOperationBlock::Multplication);
    K_HP->push_back(Inv_etha->OutputPort, BasicOperationBlock::Multplication);
    K_HP->push_back(getInputPort("vis_nom"), BasicOperationBlock::Multplication);
    K_HP->push_back(getInputPort("rho_nom"), BasicOperationBlock::Multplication);
    K_HP->push_back(getInputPort("P_nom"), BasicOperationBlock::Division);
    K_HP->OutputPort->Description = "Hagen-Poiseuille coefficient";
    K_HP->OutputPort->Symbol = "K_HP";
    K_HP->OutputPort->Dimension = "Pa";
    SystemBlocks.push_back(K_HP);

    Block_ptr K_leak( new BasicOperationBlock("K_leak") );
    K_leak->push_back(K_HP->OutputPort, BasicOperationBlock::Multplication);
    K_leak->push_back(getInputPort("vis"), BasicOperationBlock::Division);
    K_leak->push_back(getInputPort("rho"), BasicOperationBlock::Division);
    K_leak->OutputPort->Description = "Leakage coefficient";
    K_leak->OutputPort->Symbol = "K_leak";
    K_leak->OutputPort->Dimension = "-";
    SystemBlocks.push_back(K_leak);

    Block_ptr P( new BasicOperationBlock("P") );
    Block_ptr AlgLoop( new AlgabraicLoop("AlgLoop") );
    AlgLoop->push_back(P);
    SystemBlocks.push_back(AlgLoop);

    Block_ptr q( new BasicOperationBlock("q") );
    q->push_back(getInputPort("v"), BasicOperationBlock::Multplication);
    q->push_back(getInputPort("A"), BasicOperationBlock::Multplication);
    q->OutputPort->Description = "flow of the system";
    q->OutputPort->Symbol = "q";
    q->OutputPort->Dimension = "m^3/s";
    SystemBlocks.push_back(q);

    Block_ptr q_leak( new BasicOperationBlock("q_leak") );
    q_leak->push_back(K_leak->OutputPort, BasicOperationBlock::Multplication);
    q_leak->push_back(AlgLoop->OutputPort, BasicOperationBlock::Multplication);
    q->OutputPort->Description = "leakage flow of the system";
    q->OutputPort->Symbol = "q_leak";
    q->OutputPort->Dimension = "m^3/s";
    SystemBlocks.push_back(q_leak);

    Block_ptr q_tot( new BasicOperationBlock("q_tot") );
    q_tot->push_back(q->OutputPort, BasicOperationBlock::Addition);
    q_tot->push_back(q_leak->OutputPort, BasicOperationBlock::Addition);
    q_tot->OutputPort->Description = "total flow of the system";
    q_tot->OutputPort->Symbol = "q_tot";
    q_tot->OutputPort->Dimension = "m^3/s";
    SystemBlocks.push_back(q_tot);

    Block_ptr V_g( new BasicOperationBlock("V_g") );
    V_g->push_back(q_tot->OutputPort, BasicOperationBlock::Multplication);
    V_g->push_back(getInputPort("omega"), BasicOperationBlock::Division);
    V_g->OutputPort->Description = "Actual optimal displacement";
    V_g->OutputPort->Symbol = "V_g";
    V_g->OutputPort->Dimension = "m^3";
    SystemBlocks.push_back(V_g);

    Block_ptr V_g_max( new Saturation( "V_g_max" ));
    V_g_max->InputPorts.push_back(V_g->OutputPort);
    V_g_max->OutputPort->Description = "Actual displacement";
    V_g_max->OutputPort->Symbol = "V_g";
    V_g_max->OutputPort->Dimension = "m^3";
    SystemBlocks.push_back(V_g_max);

    Block_ptr q_dis( new BasicOperationBlock("q_dis") );
    q_dis->push_back(V_g_max->OutputPort, BasicOperationBlock::Multplication);
    q_dis->push_back(getInputPort("omega"), BasicOperationBlock::Multplication);
    q_dis->OutputPort->Description = "flow of the system";
    q_dis->OutputPort->Symbol = "qq_dis";
    q_dis->OutputPort->Dimension = "m^3/s";
    SystemBlocks.push_back(q_dis);

    Block_ptr dq( new BasicOperationBlock("dq") );
    dq->push_back(q->OutputPort, BasicOperationBlock::Addition);
    dq->push_back(q_dis->OutputPort, BasicOperationBlock::Subtraction);
    dq->OutputPort->Description = "flow of the system";
    dq->OutputPort->Symbol = "dq";
    dq->OutputPort->Dimension = "m^3/s";
    SystemBlocks.push_back(dq);

    P->push_back(dq->OutputPort, BasicOperationBlock::Multplication);
    P->push_back(K_leak->OutputPort, BasicOperationBlock::Division);
    P->OutputPort->Description = "Pressure of the system";
    P->OutputPort = OutputPort;
    P->OutputPorts[0] = OutputPort;
    P->OutputPort->Symbol = "P";
    P->OutputPort->Dimension = "Pa";
    OutputPort = P->OutputPort;
    SystemBlocks.push_back(P);

    Block_ptr T( new BasicOperationBlock("T") );
    T->push_back(P->OutputPort, BasicOperationBlock::Multplication);
    T->push_back(V_g_max->OutputPort, BasicOperationBlock::Multplication);
    T->push_back(getInputPort("EthaMech"), BasicOperationBlock::Multplication);
    T->OutputPort->Description = "Required Torque";
    T->OutputPort->Symbol = "T";
    T->OutputPort->Dimension = "N/m";
    OutputPorts.push_back(T->OutputPort);
    SystemBlocks.push_back(T);
    RescaleInputsMatrix(1,1);
    *P->History[0] << 250e5;
}

HydraulicPump::~HydraulicPump() {

}
}
}
