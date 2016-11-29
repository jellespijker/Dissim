/*
 * Simulation.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: peer23peer
 */

#include "Core/Simulation.h"

namespace dissim {

Simulation::Simulation() {
  Time = boost::shared_ptr<Chronos>(new Chronos);
  export_ = Export::Export_Ptr( new CSV(Time));
}

Simulation::~Simulation() {
  // TODO Auto-generated destructor stub
}

void Simulation::Run(double endtime) {
  Time->EndTime = endtime;
  export_->init();
  std::for_each(SystemBlocks.begin(), SystemBlocks.end(), [&](boost::shared_ptr<dissim::Block> &S) {
    S->setTime(Time);
  });

  while (*Time->CurrentTime < Time->EndTime) {
    std::for_each(SystemBlocks.begin(), SystemBlocks.end(), [&](boost::shared_ptr<dissim::Block> &S) {
      S->Run();
    });
    export_->log();
    Time->Progress();
  }
  Time->History.pop_back();
}

Export::Export_Ptr &Simulation::getExport() {
  return export_;
}

void Simulation::setExport(const Export::Export_Ptr &exporter) {
  Simulation::export_ = exporter;
}

} /* namespace dissim */
