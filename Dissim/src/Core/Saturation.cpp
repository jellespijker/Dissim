/*
 * Saturation.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#include "Core/Saturation.h"

namespace dissim {

Saturation::Saturation() {

}

Saturation::Saturation(std::string name) {
    this->Name = name;
    Block();
    range.first.resize(1,1);
    range.second.resize(1,1);
    range.first << std::numeric_limits<double>::min();
    range.second << std::numeric_limits<double>::max();
}

Saturation::~Saturation() {

}

DissimType::Dissim_ptr Saturation::Run() {
    for (int i = 0; i < InputPorts[0]->Value.rows(); i++) {
        for (int j = 0; j < InputPorts[0]->Value.cols(); j++) {
            if ( InputPorts[0]->Value(i, j) < range.first(i, j) ) {
                OutputPort->Value(i, j) = range.first(i, j);
            } else if ( InputPorts[0]->Value(i, j) > range.second(i, j) ) {
                OutputPort->Value(i, j) = range.second(i, j);
            } else {
                OutputPort->Value(i, j) = InputPorts[0]->Value(i, j);
            }
        }
    }
    DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>( OutputPort->Value );
    History.push_back(v);
    return OutputPort;
}

}  // namespace dissim



