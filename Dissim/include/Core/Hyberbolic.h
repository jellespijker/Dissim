#pragma once

#include "Block.h"

namespace dissim {

class Hyberbolic : public Block {
public:
  enum Operation { sinh = 10, cosh = 11, tanh = 12 };

  typedef std::vector<Hyberbolic::Operation> BasicOps_t;

  Hyberbolic();
  Hyberbolic(std::string name);
  virtual ~Hyberbolic();

  void push_back(DissimType::Dissim_ptr dissimVar, int operation);

  dissim::DissimType::Dissim_ptr Run();
};
}
