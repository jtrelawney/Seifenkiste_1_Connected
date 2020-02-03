#ifndef _TIME_CLASS
#define _TIME_CLASS

#include <chrono> // for timing stuff
using def_time_format = std::time_t;

def_time_format get_time_stamp_ns();
def_time_format get_time_stamp_ms();
def_time_format get_time_stamp();

#endif
