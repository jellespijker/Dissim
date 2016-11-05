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
