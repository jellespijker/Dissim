/*
 * DissimType.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#include <Core/DissimType.h>

namespace dissim {

DissimType::DissimType() {
    this->Value = Value_t(1, 1);
}

DissimType::DissimType(std::string symbol, std::string dimension, std::string description) {
    this->Value = Value_t(1, 1);
    this->Symbol = symbol;
    this->Dimension = dimension;
    this->Description = description;
}

DissimType::DissimType(std::string symbol, std::string dimension, std::string description, double value)  {
    DissimType(symbol, dimension, description);
    this->Value << value;
}

DissimType::~DissimType() {
	// TODO Auto-generated destructor stub
}

} /* namespace dissim */
