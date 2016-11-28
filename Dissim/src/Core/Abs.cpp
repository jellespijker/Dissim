#include "../../include/Core/Abs.h"

namespace dissim {

Abs::Abs() {

}

Abs::Abs(std::string name) {
  this->Name = name;
  Block();
}

DissimType::Dissim_ptr Abs::Run() {
  for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
    for (int j = 0; j < InputPorts[0]->Value.cols(); j++) {
      OutputPort->Value(i, j) = std::abs(InputPorts[0]->Value(i, j));
    }
  }
  if (saveHistory_) {
    DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>(OutputPort->Value);
    History.push_back(v);
  }
  return OutputPort;
}

Abs::~Abs() {}

}

