#pragma once

#include "Block.h"

namespace dissim {

class Abs: public Block {
public:
  Abs();
  Abs(std::string name);
  virtual ~Abs();

  DissimType::Dissim_ptr Run();
};
}
