/*
 * Simulation.h
 *
 *  Created on: Jun 7, 2016
 *      Author: peer23peer
 */

#pragma once

#include "Chronos.h"
#include "Block.h"
#include "Export.h"

#include <boost/shared_ptr.hpp>

#include <algorithm>

namespace dissim {

class Simulation {
public:

  Chronos::Chronos_Ptr Time;
  Block::SystemBlockVector_t SystemBlocks;

  Simulation();
  virtual ~Simulation();

  void Run(double endtime = 0.02);

  Export::Export_Ptr &getExport();
  void setExport(const Export::Export_Ptr &exporter);
private:
  Export::Export_Ptr export_;

};

} /* namespace dissim */
