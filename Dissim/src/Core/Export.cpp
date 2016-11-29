#include "Core/Export.h"
#include "sstream"

namespace  dissim {
std::string &Export::getFilename() {
  return filename_;
}

void Export::setFilename(const std::string &filename) {
  Export::filename_ = filename;
}

bool Export::isFileOpen() {
  return fileOpen_;
}

Block::IO_t &Export::getLogPorts() {
  return LogPorts_;
}

void Export::setLogPorts(const Block::IO_t &LogPorts) {
  Export::LogPorts_ = LogPorts;
}

Export::Export(Chronos::Chronos_Ptr time)
    : Time_(time),
      filename_(""),
      fileOpen_(false),
      Delta_t_(time->Delta_t) {

}

Export::~Export() {
  close();
}

void Export::open() {
  if (!filename_.empty()) {
    fs_.exceptions(std::ios::failbit | std::ios::badbit);
    fs_.open(filename_);
    fileOpen_ = true;
  }
}

void Export::open(const std::string &filename) {
  setFilename(filename);
  open();
}

void Export::push_back(DissimType::Dissim_ptr port) {
  LogPorts_.push_back(port);
}

void Export::close() {
  if (isFileOpen()) {
    fs_.close();
    fileOpen_ = false;
  }
}

double Export::getDelta_t() const {
  return Delta_t_;
}

void Export::setDelta_t(double Delta_t) {
  Export::Delta_t_ = Delta_t;
}

void Export::log() {
  size_t i = 0;
  for (auto &&port : LogPorts_) {
    DissimType::Value_ptr v = boost::make_shared<DissimType::Value_t>(port->Value);
    History_[i++].push_back(v);
  }
}

void Export::init() {
  History_.clear();
  for (auto &&port : LogPorts_) {
    std::vector<DissimType::Value_ptr> logVec;
    History_.push_back(logVec);
  }
}

void Export::write(const std::string &filename) {
  open(filename);
  write();
}

CSV::CSV(Chronos::Chronos_Ptr time)
    : Export(time),
      seperator_(",") {
}

CSV::~CSV() {
  close();
}

void CSV::write() {
  if (!fileOpen_ || LogPorts_.size() == 0) {
    return;
  }

  //Write the first time step
  std::stringstream line;
  line << *Time_->History[0] << seperator_;
  for (auto &&port : History_) {
    line << *port[0] << seperator_;
  }
  line.seekp(-1, std::ios_base::end);
  line << std::endl;
  fs_.write(line.str().c_str(), line.str().size());

  //Write consequative time steps
  double lastEntryTime = -0.00001;
  size_t i = 0;
  for (auto &&history : Time_->History)  {
    if ((*history - lastEntryTime) >= Delta_t_) {
      lastEntryTime = *history - 0.00001;
      std::stringstream line;
      line << *history << seperator_;
      for (auto &&port : History_) {
        line << *port[i] << seperator_;
      }
      line.seekp(-1, std::ios_base::end);
      line << std::endl;
      fs_.write(line.str().c_str(), line.str().size());
    }
    i++;
  }

  //Write the last time step
  line.clear(std::ios_base::goodbit);
  line << *Time_->History.back() << seperator_;
  i -= 1;
  for (auto &&port : History_) {
    line << *port[i] << seperator_;
  }
  line.seekp(-1, std::ios_base::end);
  line << std::endl;
  fs_.write(line.str().c_str(), line.str().size());
  close();
}

const std::string &CSV::getSeperator() const {
  return seperator_;
}

void CSV::setSeperator(const std::string &seperator) {
  CSV::seperator_ = seperator;
}
}