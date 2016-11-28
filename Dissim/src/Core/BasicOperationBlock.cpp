/*
 * BasicOperationBlock.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#include "Core/BasicOperationBlock.h"

namespace dissim {

BasicOperationBlock::BasicOperationBlock() {

}

BasicOperationBlock::BasicOperationBlock(std::string name) {
  this->Name = name;
  Block();
}

BasicOperationBlock::~BasicOperationBlock() {

}

dissim::DissimType::Dissim_ptr BasicOperationBlock::Run() {
  int i = 1;
  OutputPort->Value = InputPorts[0]->Value;
  std::for_each(InputPorts.begin() + 1, InputPorts.end(), [&](dissim::DissimType::Dissim_ptr &IP) {
    switch (Operations[i++]) {
    default:
    case Addition:OutputPort->Value += IP->Value;
      break;
    case Subtraction:OutputPort->Value -= IP->Value;
      break;
    case Division:OutputPort->Value = OutputPort->Value * (1 / IP->Value);
      break;
    case Multplication:OutputPort->Value = OutputPort->Value * IP->Value;
      break;
    case Power:Eigen::pow(OutputPort->Value, IP->Value);
    case Root:
      //Eigen::pow(OutputPort->Value, 1 / IP->Value);
      break;
    }
  });
  if (saveHistory_) {
    DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>(OutputPort->Value);
    History.push_back(v);
  }
  return OutputPort;
}

}



