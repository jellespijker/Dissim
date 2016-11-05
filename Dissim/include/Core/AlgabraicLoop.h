#pragma once

#include "Core/Block.h"

namespace dissim {

class AlgabraicLoop : public Block {
public:
    AlgabraicLoop();
    AlgabraicLoop(std::string name);
    virtual ~AlgabraicLoop();

    void push_back(Block::Block_ptr block);
    DissimType::Dissim_ptr Run();
};

}
