#include "Core/DissimType.h"
#include "Core/Solver.h"

#include <algorithm>
#include <vector>

#include <boost/make_shared.hpp>

namespace dissim {

Solver::Solver() {

}

Solver::~Solver() {

}

DissimType::Dissim_ptr Solver::diff(Block::Block_ptr block, DissimType::Dissim_ptr var, double h) {
  bool saveSetting = block->getSaveHistory();
  block->setSaveHistory(false);

  block->Run();
  DissimType::Dissim_ptr output(new DissimType(*block->OutputPorts[0].get()));

  var->Value += h;
  block->Run();
  DissimType::Dissim_ptr diffOut(new DissimType);
  diffOut->Value = (block->OutputPorts[0]->Value - output->Value) / h;

  block->setSaveHistory(saveSetting);
  return diffOut;
}

Newton::Newton() {

}

Newton::~Newton() {

}

void Newton::Solve(Block::Block_ptr block, DissimType::Dissim_ptr var) {


}

}

