#ifndef FDPP_HELPERS_TIME_UTILS_H
#define FDPP_HELPERS_TIME_UTILS_H

namespace fdutils {

long get_timestamp(int year, int month, int day, int hour, int minute,
                   int second);

long add_timestamp(int year, int month, int day, int hour, int minute,
                   int second, int seconds_offset);

long now_timestamp();

long add_now_timestamp(const int seconds);

} // namespace fdutils

#endif // !FDPP_HELPERS_TIME_UTILS_H
