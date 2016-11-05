/*
 * Saturation.h
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#pragma once

#include "Block.h"
#include "BasicOperationBlock.h"
#include "limits"

namespace dissim {

class Saturation: public Block {
public:

	Saturation();
    Saturation(std::string name);
	virtual ~Saturation();

    DissimType::Dissim_ptr Run();
private:

};

} /* namespace dissim */

