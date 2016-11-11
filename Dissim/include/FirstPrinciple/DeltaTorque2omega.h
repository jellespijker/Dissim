#pragma once

#include "../Core/BasicOperationBlock.h"
#include "../Core/Integrator.h"
#include "../Core/SystemBlock.h"

namespace dissim {
namespace FirstPrinciple {

class DeltaTorque2omega : public SystemBlock {
public:
    DeltaTorque2omega();
    DeltaTorque2omega(std::string name);
    virtual ~DeltaTorque2omega();
};
}
}
