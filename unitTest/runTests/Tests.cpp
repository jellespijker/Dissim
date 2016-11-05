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
    b.RescaleInputsMatrix(1,1);
    b.InputPorts[0]->Value << 10;
    b.InputPorts[1]->Value << 5;
    b.InputPorts[2]->Value <<  25;
    b.Run();
    ASSERT_EQ(b.OutputPort->Value(0,0), -10);
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
    ASSERT_EQ(b.OutputPort->Value(0,0), 2);
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
    I0->RescaleInputsMatrix(1,1);
    I0->InputPorts[0]->Value << 10;
    I0->InputPorts[1]->Value << 10;

    I1->push_back(BasicOperationBlock::Multplication);
    I1->push_back(BasicOperationBlock::Division);
    I1->RescaleInputsMatrix(1,1);
    I1->InputPorts[0] = I0->OutputPort;
    I1->InputPorts[1]->Value << 100;

    I2->push_back(BasicOperationBlock::Integrate);
    I2->RescaleInputsMatrix(1,1);
    *I2->InitialValue << 0.0;
    I2->InputPorts[0] = I1->OutputPort;

    s.Run(5);
    ASSERT_NEAR(s.SystemBlocks[2]->OutputPort->Value(0,0), 1.0, 0.005);
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
    I0->RescaleInputsMatrix(1,1);
    I0->InputPorts[0]->Value << 10;
    I0->InputPorts[1]->Value << 10;

    I1->push_back(BasicOperationBlock::Multplication);
    I1->push_back(BasicOperationBlock::Division);
    I1->RescaleInputsMatrix(1,1);
    I1->InputPorts[0] = I0->OutputPort;
    I1->InputPorts[1]->Value << 100;

    I2->push_back(BasicOperationBlock::Integrate);
    I2->RescaleInputsMatrix(1,1);
    *I2->InitialValue << 0.0;
    I2->InputPorts[0] = I1->OutputPort;

    I3->push_back(BasicOperationBlock::Saturate);
    I3->RescaleInputsMatrix(1,1);
    I3->range.first << 0;
    I3->range.second << 1;
    I3->InputPorts[0] = I2->OutputPort;

    s.Run(10);
    ASSERT_NEAR(I3->OutputPort->Value(0,0), 1.0, 0.005);
}