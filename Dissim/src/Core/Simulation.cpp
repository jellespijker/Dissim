/*
 * Simulation.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: peer23peer
 */

#include "Core/Simulation.h"

namespace dissim {

Simulation::Simulation() {
    Time = boost::shared_ptr<Chronos>( new Chronos );
}

Simulation::~Simulation() {
	// TODO Auto-generated destructor stub
}

void Simulation::Run(double endtime) {
    Time->EndTime = endtime;
    std::for_each(SystemBlocks.begin(), SystemBlocks.end(), [&](boost::shared_ptr<dissim::Block> &S){
       S->setTime(Time);
    });

    while( *Time->CurrentTime < Time->EndTime ) {
        std::for_each(SystemBlocks.begin(), SystemBlocks.end(), [&](boost::shared_ptr<dissim::Block> &S){
           S->Run();
        });
        Time->Progress();
    }
}

} /* namespace dissim */
