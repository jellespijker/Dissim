#pragma once

#include "Core/BasicOperationBlock.h"
#include "Core/Block.h"

namespace dissim {

class SystemBlock : public Block{
public:

    SystemBlock();
    SystemBlock(std::string name);

    virtual ~SystemBlock();

    void push_back(Block::Block_ptr block);
    DissimType::Dissim_ptr Run();

};

}
