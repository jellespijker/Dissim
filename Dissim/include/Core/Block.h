/*
 * Block.h
 *
 *  Created on: Jun 7, 2016
 *      Author: peer23peer
 */
#pragma once
#include <algorithm>
#include <vector>

#include <boost/make_shared.hpp>

#include "../Math/Math.h"
#include "BlockException.h"
#include "Chronos.h"
#include "DissimType.h"

namespace dissim {

class Block {
public:
  typedef std::vector<DissimType::Dissim_ptr> IO_t;
  typedef std::pair<DissimType::Value_t, DissimType::Value_t> Range_t;
  typedef boost::shared_ptr<dissim::Block> Block_ptr;
  typedef std::vector<Block_ptr> SystemBlockVector_t;

  boost::shared_ptr<Chronos> Time;
  std::vector<DissimType::Value_ptr> History;
  DissimType::Value_ptr InitialValue;
  SystemBlockVector_t SystemBlocks;

  Range_t range;
  double accuracy = 1e8;

  std::string Name;
  Block_ptr getSubBlock(std::string name);

  Block();
  Block(std::string name);
  virtual ~Block();

  virtual void push_back(DissimType::Dissim_ptr dissimVar, int operation);
  virtual void push_back(DissimType::Dissim_ptr dissimVar);
  virtual void push_back(int operation);
  virtual void push_back(Block_ptr blck);

  void RescaleInputsMatrix(int cols, int rows);
  void RescaleInputsMatrix(Block *obj, int cols, int rows);

  void setTime(boost::shared_ptr<Chronos> time);

  virtual DissimType::Dissim_ptr Run();

  DissimType::Dissim_ptr getInputPort(std::string symbol);
  DissimType::Dissim_ptr getOutputPort(std::string symbol);

  IO_t InputPorts;
  IO_t OutputPorts;
  DissimType::Dissim_ptr OutputPort;
  std::vector<int> Operations;
protected:
  void reRouteInput(Block_ptr blck);
};

} /* namespace dissim */
