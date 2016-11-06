#include "../../../include/Components/Math/K_HP.h"

namespace dissim {
namespace Components {

K_HP::K_HP() {
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "v_nom", "PA * s", "the Nominal kinematic viscosity parameter. This is "
                         "the kinematic viscosity at which the nominal "
                         "volumetric efficiency is specified.")));
  InputPorts.push_back(DissimType::Dissim_ptr(
      new DissimType("v", "PA * s", "the fluid kinematic viscosity in the "
                                    "attached hydraulic fluid network.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "rho_nom", "kg * m^-3", "the Nominal fluid density parameter. This is "
                              "the density at which the nominal volumetric "
                              "efficiency is specified.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "rho", "kg * m^-3", "the actual fluid density in the attached hydraulic "
                          "(isothermal liquid) network. This density can "
                          "differ from the Nominal fluid density parameter.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "omega_nom", "rad * s^-1",
      "the Nominal shaft angular velocity parameter. This is the angular "
      "velocity at which the nominal volumetric efficiency is specified.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "DeltaP_nom", "Pa", "the Nominal pressure drop parameter. This is the "
                          "pressure drop at which the nominal volumetric "
                          "efficiency is specified.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "eta_V_nom", "-", " the Volumetric efficiency at nominal conditions "
                        "parameter. This is the volumetric efficiency "
                        "corresponding to the specified nominal conditions.")));
  InputPorts.push_back(DissimType::Dissim_ptr(
      new DissimType("D_max", "cm^3", "the Maximum displacement parameter.")));

  DissimType::Dissim_ptr const_1(new DissimType);
  const_1->Value << 1;
  const_1->Description = "";
  const_1->Symbol = "const_1";
  const_1->Dimension = "-";

  Block_ptr a(new BasicOperationBlock("a"));
  a->push_back(getInputPort("v_nom"), BasicOperationBlock::Multplication);
  a->push_back(getInputPort("rho"), BasicOperationBlock::Division);
  a->push_back(getInputPort("v"), BasicOperationBlock::Division);
  SystemBlocks.push_back(a);

  Block_ptr b(new BasicOperationBlock("b"));
  b->push_back(getInputPort("rho_nom"), BasicOperationBlock::Multplication);
  b->push_back(getInputPort("omega_nom"), BasicOperationBlock::Multplication);
  b->push_back(getInputPort("D_max"), BasicOperationBlock::Multplication);
  b->push_back(getInputPort("DeltaP_nom"), BasicOperationBlock::Division);
  SystemBlocks.push_back(b);

  Block_ptr c(new BasicOperationBlock("c"));
  c->push_back(const_1, BasicOperationBlock::Multplication);
  c->push_back(getInputPort("eta_V_nom"), BasicOperationBlock::Division);
  SystemBlocks.push_back(c);

  Block_ptr d(new BasicOperationBlock("d"));
  d->push_back(c->OutputPort, BasicOperationBlock::Addition);
  d->push_back(const_1, BasicOperationBlock::Subtraction);
  SystemBlocks.push_back(d);

  Block_ptr e(new BasicOperationBlock("e"));
  e->push_back(a->OutputPort, BasicOperationBlock::Multplication);
  e->push_back(b->OutputPort, BasicOperationBlock::Multplication);
  e->push_back(d->OutputPort, BasicOperationBlock::Multplication);

  e->OutputPort->Dimension = "-";
  e->OutputPort->Symbol = "K_HP";
  e->OutputPort->Description = "the Hagen-Poiseuille coefficient for laminar "
                               "pipe flows. This coefficient is computed from "
                               "the specified nominal parameters.";
  OutputPort = e->OutputPort;
  SystemBlocks.push_back(e);
}

K_HP::~K_HP() {}
}
}
