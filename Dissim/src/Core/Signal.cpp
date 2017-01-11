#include "Core/Signal.h"

#include <math.h>
#include <boost/core/ignore_unused.hpp>
#include <boost/bind.hpp>

namespace dissim {

void Signal::setSetting_(const Signal::Setting_t &setting_) {
  Signal::setting_ = setting_;
}

Signal::Signal() {

}

Signal::Signal(std::string name)
    : Block(name),
      toggle_(false),
      firstRun_(true) {
}

Signal::~Signal() {

}

void Signal::setSignal(int i, int j, signal_t func) {
  if (setting_.Time < Time->Delta_t) {
    if (std::fmod<double>(*Time->CurrentTime, 2 * setting_.Time) <= setting_.Time) {
      OutputPort->Value(i,j) = func(*Time->CurrentTime, setting_.Time, Time->Delta_t, );
    } else {
      if (firstRun_) {
        firstRun_ = false;
      }
      OutputPort->Value(i,j) = func();
    }
  } else {
    if (toggle_) {
      OutputPort->Value(i,j) = func();
    } else {
      if (firstRun_) {
        firstRun_ =  false;
      }
      OutputPort->Value(i,j) = func();
    }
    toggle_ ^= toggle_;
  }
}

DissimType::Dissim_ptr Signal::Run() {
  for (int i = 0; i < OutputPort->Value.cols(); ++i) {
    for (int j = 0; j < OutputPort->Value.rows(); ++j) {
      switch (Operations[0]) {
      default:
      case Constant:
        setSignal(i,j, boost::bind(Signal::constSignal, &this));
        break;
      case Pulse:
        setSignal(i, j, boost::bind(pulseSignal, &this));
        break;
      case Ramp:
        setSignal(i, j, boost::bind(rampSignal, &this));
        break;
      case Sinus:
        setSignal(i,j, boost::bind(sinusSignal, &this));
        break;
      case Sawtooth:
        setSignal(i,j, boost::bind(sawtoothSignal, &this));
        break;
      }
    }

  }
}

double Signal::constSignal(double currentTime, double dt, double resolution) {
  boost::ignore_unused(currentTime, dt, resolution);
  return setting.Amplitude;;
}

}
