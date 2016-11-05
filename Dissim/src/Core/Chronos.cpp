#include "Core/Chronos.h"

namespace dissim {

Chronos::Chronos() {
    boost::shared_ptr<double> v( new double );
    *v = 0.0;
    History.push_back(v);
    CurrentTime = History[0];
}

Chronos::~Chronos() {

}

boost::shared_ptr<double> Chronos::Progress() {
    boost::shared_ptr<double> v( new double );
    *v = *History[History.size()  - 1] + Delta_t;
    History.push_back(v);
    CurrentTime = History[History.size() - 1];
    return CurrentTime;
}

}
