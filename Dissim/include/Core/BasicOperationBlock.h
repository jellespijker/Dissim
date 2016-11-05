/*
 * BasicOperationBlock.h
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#ifndef DISSIM_BASICOPERATIONBLOCK_H_
#define DISSIM_BASICOPERATIONBLOCK_H_

#include "Block.h"

namespace dissim {

class BasicOperationBlock: public Block {
public:
	enum Operation {
         Addition = 1,
         Subtraction = 2,
         Division = 3,
         Multplication = 4,
         Power = 5,
         Root = 6,
         Integrate = 7,
         Saturate = 8
	};

    typedef std::vector<BasicOperationBlock::Operation> BasicOps_t;

	BasicOperationBlock();
    BasicOperationBlock(std::string name);
	virtual ~BasicOperationBlock();

    DissimType::Dissim_ptr Run();
private:

};

} /* namespace dissim */

#endif /* DISSIM_BASICOPERATIONBLOCK_H_ */
