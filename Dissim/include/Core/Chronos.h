#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

namespace dissim {

class Chronos {

public:
  typedef std::vector<boost::shared_ptr<double>> time_t;
  typedef boost::shared_ptr<Chronos> Chronos_Ptr;

  time_t History;
  boost::shared_ptr<double> CurrentTime;

  double Delta_t = 0.02;
  double EndTime = 0.02;

  Chronos();
  virtual ~Chronos();

  boost::shared_ptr<double> Progress();
};

}
