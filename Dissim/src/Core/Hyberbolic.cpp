#include "../../include/Core/Hyberbolic.h"
#include <cmath>

namespace dissim {

Hyberbolic::Hyberbolic() {}

Hyberbolic::Hyberbolic(std::string name) {
  this->Name = name;
  Block();
}

Hyberbolic::~Hyberbolic() {}

dissim::DissimType::Dissim_ptr Hyberbolic::Run() {
  switch (Operations[0]) {
  case sinh:
    for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
      for (int j = 0; j < InputPorts[0]->Value.cols(); ++j) {
        OutputPort->Value(i, j) = std::sinh(InputPorts[0]->Value(i, j));
      }
    }
    break;
  case cosh:
    for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
      for (int j = 0; j < InputPorts[0]->Value.cols(); ++j) {
        OutputPort->Value(i, j) = std::cosh(InputPorts[0]->Value(i, j));
      }
    }
    break;
  case tanh:
    for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
      for (int j = 0; j < InputPorts[0]->Value.cols(); ++j) {
        OutputPort->Value(i, j) = std::tanh(InputPorts[0]->Value(i, j));
      }
    }
    break;
  default:
    for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
      for (int j = 0; j < InputPorts[0]->Value.cols(); ++j) {
        OutputPort->Value(i, j) = InputPorts[0]->Value(i, j);
      }
    }
    break;
  }
  DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>( OutputPort->Value );
  History.push_back(v);
  return OutputPort;
}
void Hyberbolic::push_back(DissimType::Dissim_ptr dissimVar, int operation) {
  Block::push_back(dissimVar, operation);
}
}
