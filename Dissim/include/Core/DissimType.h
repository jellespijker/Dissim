/*
 * DissimType.h
 *
 *  Created on: Jun 9, 2016
 *      Author: peer23peer
 */

#pragma once

#include <Eigen/Core>
#include <Eigen/Dense>

#include <string>

#include <boost/shared_ptr.hpp>

namespace dissim {

class DissimType {
public:
	typedef boost::shared_ptr<dissim::DissimType> Dissim_ptr;
    typedef Eigen::ArrayXXd Value_t;
    typedef boost::shared_ptr<DissimType::Value_t> Value_ptr;

	DissimType();
    DissimType(std::string symbol, std::string dimension, std::string description = "");
    DissimType(std::string symbol, std::string dimension, std::string description, double value);
	virtual ~DissimType();

    Value_t Value;
	std::string Symbol = "";
	std::string Dimension = "";
    std::string Description = "";
};

} /* namespace dissim */
