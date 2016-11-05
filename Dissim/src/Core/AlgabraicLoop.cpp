#include "Core/AlgabraicLoop.h"

namespace dissim {

AlgabraicLoop::AlgabraicLoop() {

}

AlgabraicLoop::AlgabraicLoop(std::string name) {
    this->Name = name;
    AlgabraicLoop();
}

AlgabraicLoop::~AlgabraicLoop() {

}

void AlgabraicLoop::push_back(Block_ptr block) {
    SystemBlocks.push_back(block);
    OutputPort = block->OutputPort;
    OutputPorts = block->OutputPorts;
    OutputPort->Value = *block->History[block->History.size() - 1];
}

DissimType::Dissim_ptr AlgabraicLoop::Run() {
    OutputPort->Value = *SystemBlocks[0]->History[SystemBlocks[0]->History.size() - 1];
    return OutputPort;
}

}
