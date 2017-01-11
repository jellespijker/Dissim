#pragma once

#include "Block.h"
#include <boost/function.hpp>

namespace dissim {

class Signal : public Block {
public:
  typedef struct Setting {
    bool Loop = false;
    double Amplitude = 1.0;
    double Time = 0.0;
    double Mean = 0.0;
  } Setting_t;

  enum Operation {
    Constant = 20,
    Pulse = 21,
    Ramp = 22,
    Sinus = 23,
    Sawtooth = 24
  };

  typedef boost::function<double(double, double, double)> signal_t;

  Signal();
  Signal(std::string name);
  virtual ~Signal();

  DissimType::Dissim_ptr Run();

  void setSetting_(const Setting_t &setting_);
private:
  Setting_t setting_;
  bool toggle_;
  bool firstRun_;

  void setSignal(int i, int j, signal_t func);
  double constSignal(double currentTime, double dt, double resolution);
  double pulseSignal(double currentTime, double dt, double resolution);
  double rampSignal(double currentTime, double dt, double resolution);
  double sinusSignal(double currentTime, double dt, double resolution);
  double sawtoothSignal(double currentTime, double dt, double resolution);
};

}