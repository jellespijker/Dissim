/*
 * Simulation.h
 *
 *  Created on: Jun 7, 2016
 *      Author: peer23peer
 */

#pragma once

#include "Chronos.h"
#include "Block.h"

#include <boost/shared_ptr.hpp>

#include <algorithm>

namespace dissim {

class Simulation {
public:

    boost::shared_ptr<Chronos> Time;
    Block::SystemBlockVector_t SystemBlocks;

	Simulation();
	virtual ~Simulation();

    void Run(double endtime = 0.02);

};

} /* namespace dissim */
