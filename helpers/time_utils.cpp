#include "time_utils.h"
#include <chrono>
#include <ctime>

long fdutils::get_timestamp(int year, int month, int day, int hour, int minute,
                            int second) {
  std::tm tm{};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;
  tm.tm_hour = hour;
  tm.tm_min = minute;
  tm.tm_sec = second;
  std::time_t t = std::mktime(&tm);
  return t;
}

long fdutils::add_timestamp(int year, int month, int day, int hour, int minute,
                            int second, int seconds_offset) {
  return get_timestamp(year, month, day, hour, minute, second) + seconds_offset;
}

long fdutils::now_timestamp() {
  return std::chrono::duration_cast<std::chrono::seconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}

long fdutils::add_now_timestamp(const int seconds) {
  return now_timestamp() + seconds;
}
