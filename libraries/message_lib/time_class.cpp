#include <time_class.hpp>
def_time_format get_time_stamp_ns(){
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    return nanoseconds.count();
}

def_time_format get_time_stamp_ms(){
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    //auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return milliseconds.count();
}

def_time_format get_time_stamp(){
    return get_time_stamp_ms();
}
