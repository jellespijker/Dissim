#include "Core/DissimType.h"
#include "Core/Solver.h"

#include <algorithm>
#include <vector>
#include <utility>

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
  bool saveSetting = block->getSaveHistory();
  block->setSaveHistory(false);
  DissimType::Value_t error;
  error.resize(var->Value.rows(),var->Value.rows());
  for (int i = 0; i < var->Value.rows(); i++){
    for (int j = 0; j < var->Value.cols(); ++j) {
      error(i,j) = 0.001;
    }
  }

  bool optimized = false;
  std::pair<DissimType::Dissim_ptr, DissimType::Dissim_ptr> xn;
  xn.first = var;
  xn.second = DissimType::Dissim_ptr(new DissimType);

  while (!optimized) {
    DissimType::Dissim_ptr f(block->Run());
    DissimType::Dissim_ptr fPrime(diff(block, xn.first, 0.001));
    DissimType::Value_t difference = f->Value * fPrime->Value.inverse();
    xn.second->Value = xn.first->Value - difference;
    DissimType::Value_t diffIter = xn.second->Value - xn.first->Value;
    for (int i = 0; i < error.rows(); ++i) {
      for (int j = 0; j < error.cols(); ++j) {
        if (diffIter(i,j) < error(i,j)) {
          optimized = true;
        } else {
          optimized = false;
        }
      }
    }
    xn.first->Value = xn.second->Value;
  }
  block->setSaveHistory(saveSetting);
}

}

