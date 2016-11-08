#pragma once

#include "../../Core/SystemBlock.h"

namespace dissim {
namespace Components {

class K_HP : public SystemBlock {
public:
  K_HP(bool inverted = false);
  K_HP(std::string name);
  virtual ~K_HP();
private:
  bool inverted_;
};
}
}
