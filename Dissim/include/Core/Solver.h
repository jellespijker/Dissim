#pragma once

#include <boost/shared_ptr.hpp>
#include "Block.h"
#include <vector>

namespace dissim {

class Solver {
public:
  typedef boost::shared_ptr<dissim::Solver> Solver_ptr;

  Solver();
  virtual ~Solver();

  virtual void Solve(Block::Block_ptr block, DissimType::Dissim_ptr var) = 0;

  DissimType::Dissim_ptr diff(Block::Block_ptr block, DissimType::Dissim_ptr var, double h);

protected:
  Block::Block_ptr SystemBlock_;
};

class Newton : public Solver {
public:

  Newton();
  virtual ~Newton();

  virtual void Solve(Block::Block_ptr block,  DissimType::Dissim_ptr var);
};

}

