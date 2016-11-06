#include "../../../include/Components/Math/tau_friction.h"
#include "../../../include/Core/Abs.h"
#include "../../../include/Core/Hyberbolic.h"

namespace dissim {
namespace Components {

tau_friction::tau_friction() {
  InputPorts.push_back(DissimType::Dissim_ptr(
      new DissimType("tau_0", "N * m", "the No-load torque parameter.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "K_TP", "-",
      "the Friction torque vs pressure drop coefficient parameter")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "omega_thres", "rad * s^-1",
      "the threshold angular velocity for the motor-pump transition. The "
      "threshold angular velocity is an internally set fraction of the Nominal "
      "shaft angular velocity parameter.")));
  InputPorts.push_back(DissimType::Dissim_ptr(new DissimType(
      "DeltaP", "Pa", "the pressure drop from inlet to outlet.")));
  InputPorts.push_back(DissimType::Dissim_ptr(
      new DissimType("omega", "rad * s^-1", "the shaft angular velocity.")));

  DissimType::Dissim_ptr const_4(new DissimType);
  const_4->Value << 4;
  const_4->Description = "";
  const_4->Symbol = "const_4";
  const_4->Dimension = "-";

  Block_ptr a(new Abs("a"));
  a->push_back(getInputPort("DeltaP"));
  SystemBlocks.push_back(a);

  Block_ptr b(new BasicOperationBlock("b"));
  b->push_back(getInputPort("K_TP"), BasicOperationBlock::Multplication);
  b->push_back(a->OutputPort, BasicOperationBlock::Multplication);
  SystemBlocks.push_back(b);

  Block_ptr c(new BasicOperationBlock("c"));
  c->push_back(getInputPort("tau_0"), BasicOperationBlock::Addition);
  c->push_back(b->OutputPort, BasicOperationBlock::Addition);
  SystemBlocks.push_back(c);

  Block_ptr d(new BasicOperationBlock("d"));
  d->push_back(const_4, BasicOperationBlock::Multplication);
  d->push_back(getInputPort("omega"), BasicOperationBlock::Multplication);
  d->push_back(getInputPort("omega_thres"), BasicOperationBlock::Division);
  SystemBlocks.push_back(d);

  Block_ptr e(new Hyberbolic("e"));
  e->push_back(d->OutputPort, Hyberbolic::tanh);
  SystemBlocks.push_back(e);

  Block_ptr f(new BasicOperationBlock("f"));
  f->push_back(c->OutputPort, BasicOperationBlock::Multplication);
  f->push_back(e->OutputPort, BasicOperationBlock::Multplication);
  OutputPort = f->OutputPort;
  SystemBlocks.push_back(f);
}

tau_friction::~tau_friction() {}
}
}
