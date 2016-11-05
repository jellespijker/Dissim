#include "Core/SystemBlock.h"

namespace dissim {

SystemBlock::SystemBlock() {

}

SystemBlock::SystemBlock( std::string name ) {
    this->Name = name;
    Block();
}

SystemBlock::~SystemBlock() {

}

void SystemBlock::push_back(Block::Block_ptr block) {
    SystemBlocks.push_back(block);
}

DissimType::Dissim_ptr SystemBlock::Run() {
    std::for_each(SystemBlocks.begin(), SystemBlocks.end(),[](Block::Block_ptr &B){
        B->Run();
    });
    return OutputPort;
}

}
