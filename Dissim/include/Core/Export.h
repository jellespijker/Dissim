#pragma once

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "Block.h"
#include "Chronos.h"

namespace dissim {

class Export {
public:
  typedef boost::shared_ptr<Export> Export_Ptr;

  Export(Chronos::Chronos_Ptr time);
  virtual ~Export();

  std::string &getFilename();
  void setFilename(const std::string &filename);

  void open();
  void open(const std::string &filename);

  void close();

  bool isFileOpen();

  Block::IO_t &getLogPorts();
  void setLogPorts(const Block::IO_t &LogPorts);
  void push_back(DissimType::Dissim_ptr port);

  virtual void write() = 0;
  virtual void write(const std::string &filename);

  void log();

  void init();

  double getDelta_t() const;
  void setDelta_t(double Delta_t);
protected:
  std::string filename_;
  std::ofstream fs_;
  bool fileOpen_;
  Block::IO_t LogPorts_;
  Chronos::Chronos_Ptr Time_;
  double Delta_t_;
  std::vector<std::vector<DissimType::Value_ptr>> History_;
};

class CSV : public Export {
public:

  CSV(Chronos::Chronos_Ptr time);
  ~CSV();

  virtual void write();

protected:
  std::string seperator_;
public:
  const std::string &getSeperator() const;
  void setSeperator(const std::string &seperator);

};
}
