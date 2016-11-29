//
// Created by peer23peer on 11/5/16.
//

#include "gtest/gtest.h"

#include "../../Dissim/include/dissim.h"

TEST(BasicOperations, Sum) {
  using namespace dissim;
  BasicOperationBlock b;
  b.push_back(BasicOperationBlock::Addition);
  b.push_back(BasicOperationBlock::Addition);
  b.push_back(BasicOperationBlock::Subtraction);
  b.RescaleInputsMatrix(1, 1);
  b.InputPorts[0]->Value << 10;
  b.InputPorts[1]->Value << 5;
  b.InputPorts[2]->Value << 25;
  b.Run();
  ASSERT_EQ(b.OutputPort->Value(0, 0), -10);
}

TEST(BasicOperations, MultiplicationAndDivision) {
  using namespace dissim;
  BasicOperationBlock b;
  b.push_back(BasicOperationBlock::Multplication);
  b.push_back(BasicOperationBlock::Multplication);
  b.push_back(BasicOperationBlock::Division);
  b.InputPorts[0]->Value << 10;
  b.InputPorts[1]->Value << 5;
  b.InputPorts[2]->Value << 25;
  b.Run();
  ASSERT_EQ(b.OutputPort->Value(0, 0), 2);
}

TEST(BasicOperations, Abs) {
  using namespace dissim;
  Abs a;

  DissimType::Dissim_ptr const_neg1(new DissimType);
  const_neg1->Value << -1;
  const_neg1->Description = "";
  const_neg1->Symbol = "const_1";
  const_neg1->Dimension = "-";

  a.InputPorts.push_back(const_neg1);
  a.Run();
  ASSERT_EQ(a.OutputPort->Value(0,0), 1);
}

TEST(BasicOperations, tanh) {
  using  namespace dissim;
  Block::Block_ptr h(new Hyberbolic);

  DissimType::Dissim_ptr constValue(new DissimType);
  constValue->Value << 0.693147;

  h->push_back(constValue, Hyberbolic::tanh);
  h->Run();
  ASSERT_NEAR(h->OutputPort->Value(0,0), 0.6, 0.05);

}

TEST(BasicOperations, Integrate) {
  using namespace dissim;
  Simulation s;
  Block::Block_ptr I0(new BasicOperationBlock);
  Block::Block_ptr I1(new BasicOperationBlock);
  Block::Block_ptr I2(new Integrator);
  s.SystemBlocks.push_back(I0);
  s.SystemBlocks.push_back(I1);
  s.SystemBlocks.push_back(I2);

  I0->push_back(BasicOperationBlock::Addition);
  I0->push_back(BasicOperationBlock::Addition);
  I0->RescaleInputsMatrix(1, 1);
  I0->InputPorts[0]->Value << 10;
  I0->InputPorts[1]->Value << 10;

  I1->push_back(BasicOperationBlock::Multplication);
  I1->push_back(BasicOperationBlock::Division);
  I1->RescaleInputsMatrix(1, 1);
  I1->InputPorts[0] = I0->OutputPort;
  I1->InputPorts[1]->Value << 100;

  I2->push_back(BasicOperationBlock::Integrate);
  I2->RescaleInputsMatrix(1, 1);
  *I2->InitialValue << 0.0;
  I2->InputPorts[0] = I1->OutputPort;

  s.Run(5);
  ASSERT_NEAR(s.SystemBlocks[2]->OutputPort->Value(0, 0), 1.0, 0.005);
}

TEST(BasicOperations, Saturation) {
  using namespace dissim;
  Simulation s;
  Block::Block_ptr I0(new BasicOperationBlock);
  Block::Block_ptr I1(new BasicOperationBlock);
  Block::Block_ptr I2(new Integrator);
  Block::Block_ptr I3(new Saturation);
  s.SystemBlocks.push_back(I0);
  s.SystemBlocks.push_back(I1);
  s.SystemBlocks.push_back(I2);
  s.SystemBlocks.push_back(I3);

  I0->push_back(BasicOperationBlock::Addition);
  I0->push_back(BasicOperationBlock::Addition);
  I0->RescaleInputsMatrix(1, 1);
  I0->InputPorts[0]->Value << 10;
  I0->InputPorts[1]->Value << 10;

  I1->push_back(BasicOperationBlock::Multplication);
  I1->push_back(BasicOperationBlock::Division);
  I1->RescaleInputsMatrix(1, 1);
  I1->InputPorts[0] = I0->OutputPort;
  I1->InputPorts[1]->Value << 100;

  I2->push_back(BasicOperationBlock::Integrate);
  I2->RescaleInputsMatrix(1, 1);
  *I2->InitialValue << 0.0;
  I2->InputPorts[0] = I1->OutputPort;

  I3->push_back(BasicOperationBlock::Saturate);
  I3->RescaleInputsMatrix(1, 1);
  I3->range.first << 0;
  I3->range.second << 1;
  I3->InputPorts[0] = I2->OutputPort;

  s.Run(10);
  ASSERT_NEAR(I3->OutputPort->Value(0, 0), 1.0, 0.005);
}

TEST(FirstPrinciple, DeltaTorque2omega) {
  using namespace dissim;
  Simulation s;
  Block::Block_ptr dTO(new FirstPrinciple::DeltaTorque2omega);
  s.SystemBlocks.push_back(dTO);

  dTO->RescaleInputsMatrix(1, 1);
  dTO->getInputPort("T_d")->Value << 10;
  dTO->getInputPort("T_n")->Value << 9;
  dTO->getInputPort("J")->Value << 2;

  s.Run(10);
  ASSERT_NEAR(dTO->getOutputPort("omega")->Value(0, 0), 5, 0.05);
}

TEST(Components, ElectroMotor) {
  using namespace dissim;
  Simulation s;
  Block::Block_ptr EMotor(new Components::ElectroMotor);
  s.SystemBlocks.push_back(EMotor);

  EMotor->RescaleInputsMatrix(1, 1);
  EMotor->getInputPort("P")->Value << 100;
  EMotor->getInputPort("omega")->Value << 5;
  EMotor->getSubBlock("T")->range.first << 0;
  EMotor->getSubBlock("T")->range.second << 120;

  s.Run();
  ASSERT_NEAR(EMotor->OutputPort->Value(0, 0), 20, 0.05);
}

TEST(Math, K_HP) {
  using namespace dissim::Components;
  using namespace dissim;
  Simulation s;
  Block::Block_ptr k_hp(new Components::K_HP(true));
  s.SystemBlocks.push_back(k_hp);

  k_hp->getInputPort("v_nom")->Value << 10;
  k_hp->getInputPort("rho")->Value << 999;
  k_hp->getInputPort("v")->Value << 10;
  k_hp->getInputPort("rho_nom")->Value << 1000;
  k_hp->getInputPort("omega_nom")->Value << 3;
  k_hp->getInputPort("D_max")->Value << 300;
  k_hp->getInputPort("DeltaP_nom")->Value << 2;
  k_hp->getInputPort("eta_V_nom")->Value << 0.9;

  s.Run();
  ASSERT_NEAR(k_hp->OutputPort->Value(0,0), 50.0501, 0.05);
}

TEST(Math, tau_friction) {
  using namespace dissim::Components;
  using namespace dissim;

  Simulation s;
  Block::Block_ptr t(new Components::tau_friction);
  s.SystemBlocks.push_back(t);

  t->getInputPort("tau_0")->Value << 1000;
  t->getInputPort("K_TP")->Value << 0.9;
  t->getInputPort("omega_thres")->Value << 5;
  t->getInputPort("DeltaP")->Value << 2;
  t->getInputPort("omega")->Value << 3;

  s.Run();
  ASSERT_NEAR(t->OutputPort->Value(0,0), 985.445, 0.05);
}

TEST(Components, HydraulicMotor) {
  using namespace dissim::Components;
  using namespace dissim;

  Simulation s;
  Block::Block_ptr h(new Components::HydraulicMotor);
  s.SystemBlocks.push_back(h);

  h->getInputPort("v_nom")->Value << 300;
  h->getInputPort("rho")->Value << 700;
  h->getInputPort("v")->Value << 290;
  h->getInputPort("rho_nom")->Value << 710;
  h->getInputPort("omega_nom")->Value << 5;
  h->getInputPort("D_max")->Value << 300;
  h->getInputPort("DeltaP_nom")->Value << 2;
  h->getInputPort("eta_V_nom")->Value << 0.9;
  h->getInputPort("tau_0")->Value << 1000;
  h->getInputPort("K_TP")->Value << 0.9;
  h->getInputPort("omega_thres")->Value << 5;
  h->getInputPort("DeltaP")->Value << 2;
  h->getInputPort("omega")->Value << 3;
  h->getInputPort("v_f")->Value << 3;
  h->getInputPort("A_p")->Value << (3.1415/4) * std::pow(0.15d, 2);
  h->getInputPort("D")->Value << 300;

  s.Run();
  ASSERT_NEAR(h->getOutputPort("DeltaP")->Value(0,0), -10.2924, 0.05 );
  ASSERT_NEAR(h->getOutputPort("tau")->Value(0,0), -4080.51, 10);
}

TEST(Components, HydraulicPump) {
  using namespace dissim::Components;
  using namespace dissim;

  Simulation s;
  Block::Block_ptr h(new Components::HydraulicMotor);
  s.SystemBlocks.push_back(h);

  h->getInputPort("v_nom")->Value << 300;
  h->getInputPort("rho")->Value << 700;
  h->getInputPort("v")->Value << 290;
  h->getInputPort("rho_nom")->Value << 710;
  h->getInputPort("omega_nom")->Value << 5;
  h->getInputPort("D_max")->Value << 300;
  h->getInputPort("DeltaP_nom")->Value << 2;
  h->getInputPort("eta_V_nom")->Value << 0.9;
  h->getInputPort("tau_0")->Value << 1000;
  h->getInputPort("K_TP")->Value << 0.9;
  h->getInputPort("omega_thres")->Value << 5;
  h->getInputPort("DeltaP")->Value << 2;
  h->getInputPort("omega")->Value << 3;
  h->getInputPort("v_f")->Value << 3;
  h->getInputPort("A_p")->Value << (3.1415/4) * std::pow(0.15d, 2);
  h->getInputPort("D")->Value << 300;

  s.Run();
  ASSERT_NEAR(h->getOutputPort("DeltaP")->Value(0,0), -10.2924, 0.05 );
  ASSERT_NEAR(h->getOutputPort("tau")->Value(0,0), -4080.51, 10);
}

TEST(Solver, Derivative) {
  using namespace dissim;

  Block::Block_ptr b(new BasicOperationBlock);
  b->push_back(BasicOperationBlock::Addition);
  b->push_back(BasicOperationBlock::Subtraction);
  b->RescaleInputsMatrix(1, 1);
  b->InputPorts[0]->Value << 1;
  b->InputPorts[1]->Value << 2;

  Block::Block_ptr c(new BasicOperationBlock);
  c->push_back(BasicOperationBlock::Multplication);
  c->push_back(BasicOperationBlock::Multplication);
  c->RescaleInputsMatrix(1, 1);
  c->InputPorts[0] = b->OutputPorts[0];
  c->InputPorts[1]->Value << 3;

  Block::Block_ptr a(new SystemBlock);
  a->SystemBlocks.push_back(b);
  a->SystemBlocks.push_back(c);
  a->InputPorts.push_back(b->InputPorts[0]);
  a->InputPorts.push_back(b->InputPorts[1]);
  a->InputPorts.push_back(c->InputPorts[1]);
  a->OutputPorts[0] = c->OutputPorts[0];
  Solver::Solver_ptr s( new Newton());
  a->setSolver(s);
  Block::IO_t inputs = a->InputPorts;
  DissimType::Dissim_ptr outputs = s->diff(a, a->InputPorts[0], 0.1);
  ASSERT_NEAR(outputs->Value(0,0), 3, 0.0001);
}

TEST(Solver, Newton) {
  using namespace dissim;

  Block::Block_ptr b(new BasicOperationBlock);
  b->push_back(BasicOperationBlock::Addition);
  b->push_back(BasicOperationBlock::Subtraction);
  b->RescaleInputsMatrix(1, 1);
  b->InputPorts[0]->Value << 1;
  b->InputPorts[1]->Value << 2;
  b->init();

  Block::Block_ptr c(new BasicOperationBlock);
  c->push_back(BasicOperationBlock::Multplication);
  c->push_back(BasicOperationBlock::Multplication);
  c->RescaleInputsMatrix(1, 1);
  c->InputPorts[0] = b->OutputPorts[0];
  c->InputPorts[1]->Value << 3;
  c->init();

  Block::Block_ptr a(new SystemBlock);
  a->SystemBlocks.push_back(b);
  a->SystemBlocks.push_back(c);
  a->InputPorts.push_back(b->InputPorts[0]);
  a->InputPorts.push_back(b->InputPorts[1]);
  a->InputPorts.push_back(c->InputPorts[1]);
  a->OutputPorts[0] = c->OutputPorts[0];
  Solver::Solver_ptr s( new Newton());
  a->setSolver(s);
  a->init();
  Block::IO_t inputs = a->InputPorts;
  s->Solve(a, a->InputPorts[0]);
  ASSERT_NEAR(a->InputPorts[0]->Value(0,0), 2, 0.0001);
}

TEST(Simulation, Export_to_CSV) {
  using namespace dissim::Components;
  using namespace dissim;

  Simulation s;
  Block::Block_ptr h(new Components::HydraulicMotor);
  s.SystemBlocks.push_back(h);

  h->getInputPort("v_nom")->Value << 300;
  h->getInputPort("rho")->Value << 700;
  h->getInputPort("v")->Value << 290;
  h->getInputPort("rho_nom")->Value << 710;
  h->getInputPort("omega_nom")->Value << 5;
  h->getInputPort("D_max")->Value << 300;
  h->getInputPort("DeltaP_nom")->Value << 2;
  h->getInputPort("eta_V_nom")->Value << 0.9;
  h->getInputPort("tau_0")->Value << 1000;
  h->getInputPort("K_TP")->Value << 0.9;
  h->getInputPort("omega_thres")->Value << 5;
  h->getInputPort("DeltaP")->Value << 2;
  h->getInputPort("omega")->Value << 3;
  h->getInputPort("v_f")->Value << 3;
  h->getInputPort("A_p")->Value << (3.1415/4) * std::pow(0.15d, 2);
  h->getInputPort("D")->Value << 300;
  h->init();

  s.getExport()->push_back(h->getInputPort("v_nom"));
  s.getExport()->push_back(h->OutputPort);
  s.getExport()->setDelta_t(0.2);

  s.Run(1);
  s.getExport()->write("test.dat");
}
