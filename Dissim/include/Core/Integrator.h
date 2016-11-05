/*
 * Integrator.h
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#pragma once

#include "Block.h"

#include <vector>

#include <boost/shared_ptr.hpp>

namespace dissim {

class Integrator: public Block {
public:

	Integrator();
    Integrator( std::string Name );

	virtual ~Integrator();

    DissimType::Dissim_ptr Run();
};

} /* namespace dissim */

