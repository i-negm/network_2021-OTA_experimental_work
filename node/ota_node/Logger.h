#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Arduino.h>

class Logger
{
  public:
  static void init(void);
  static void debug(String fmt);
  static void error(String fmt);
  static void warn(String fmt);
};

#endif /*__LOGGER_H__*/
