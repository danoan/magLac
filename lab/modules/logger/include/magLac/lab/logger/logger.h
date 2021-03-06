#ifndef MAGLAC_LAB_LOGGER_LOGGER_H
#define MAGLAC_LAB_LOGGER_LOGGER_H

#include <sstream>
#include <ctime>
#include <boost/filesystem.hpp>
#include <boost/date_time.hpp>

namespace magLac {
class Logger {
 public:
  enum FormattingType { HeaderOne, HeaderTwo, Normal };

  template<class TClass>
  struct LoggableObject {
    LoggableObject(const TClass &object, const std::string &name) : object(object), name(name) {}

    const TClass &object;
    const std::string name;
  };

  Logger(std::ostream &os, bool exportObjects);

  std::ostream &stream() { return os; }

  void startTimer();
  void endTimer();

  Logger &operator<<(bool b);
  Logger &operator<<(FormattingType fr);

  template<class TClass>
  unsigned int length(const TClass &s);

  template<class TClass>
  void headerOne(const TClass &s);

  template<class TClass>
  void headerTwo(const TClass &s);

  template<class TClass>
  void normal(const TClass &s);

  template<class TClass>
  Logger &operator<<(const TClass &s);

  template<class TClass>
  Logger &operator<<(const LoggableObject<TClass> &s);

  template<class TClass>
  Logger &operator-(const TClass &object);

  template<class TClass>
  Logger &operator^(const TClass &object);

  void changeOutputFolder(const std::string &newOutputFolder);

  std::string buffer();

 private:
  std::ostream &os;
  std::string outputFolder;
  bool exportObjectsFlag;

  std::stringstream ss;

  FormattingType ft;
  boost::posix_time::ptime startTime;
  boost::posix_time::ptime endTime;
};

#include "logger.hpp"

}

#endif //MAGLAC_LAB_LOGGER_LOGGER_H
