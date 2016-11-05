/*
 * Integrator.cpp
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#include "Core/Integrator.h"

namespace dissim {

Integrator::Integrator() {

}

Integrator::Integrator( std::string name ) {
    this->Name = name;
    Block();
}

Integrator::~Integrator() {

}

DissimType::Dissim_ptr Integrator::Run() {
    OutputPort->Value = (Time->Delta_t * InputPorts[0]->Value) + *History[History.size() - 1];
    DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>(OutputPort->Value);
    History.push_back( v );
    return OutputPort;
}

}  // namespace dissim



