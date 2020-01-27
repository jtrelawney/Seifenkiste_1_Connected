#ifndef ADDRESS_CLASS_H_
#define ADDRESS_CLASS_H_

#include <iostream>                 // cout

// this class defines the hardwoare platforms, sensors, and processes
// the message class allows to manage the metadata and data of a data source and the
// address as a combination of the three uniquely defines a data source, a sender or a recipient

class address_class{
public:
    enum class Platform_def : int {  undefined_platform = 0,
                                    arduino = 1,
                                    rpi = 2,
                                    pc = 3
                                };
    enum class Sensor_def : int {    undefined_sensor = 0,
                                    camera1 = 1,
                                    usonic1 = 2,
                                    imu1 = 3,
                                    time_snapshot =4
                                };

    enum Process_def : int {   cockpit = 0,
                                    tcp_client = 1,
                                    tcp_server = 2,
                                    undefined = 3,
                                    MAX_PROCESS_COUNT = undefined
                                };

    // need this for initializing an empty address, since recipient may not be known during message creation
    address_class();
    // the standard constructor to be used
    address_class(Platform_def platform, Sensor_def sensor, Process_def process);

    // functions to print and retrieve the address information
    void print_platform() const;
    void print_sensor();
    void print_process();

    Platform_def get_platform() const;
    Sensor_def get_sensor() const;
    Process_def get_process() const;

    // each process has an index, which allows to compare reciepents with process ids
    //int get_process_index() const;

    // output stuff
    friend std::ostream& operator<<(std::ostream& out, const address_class::Platform_def& platform);
    friend std::ostream& operator<<(std::ostream& out, const address_class& address);
    friend std::ostream& operator<<(std::ostream& out, const address_class::Sensor_def& sensor);
    friend std::ostream& operator<<(std::ostream& out, const address_class::Process_def& process);

    // compares 2 address, e.g. when messages are retrieved from a queue
    // currently equality is defined as valid when the process ids are the samee
    bool operator==(const address_class& other_address);
    //bool operator()(const address_class& a, const address_class& b);
    // this is required for using std:map, it needs a comparison
    bool operator<(const address_class& other) const;

private:
    Platform_def m_platform;
    Sensor_def m_sensor;
    Process_def m_process;
};

#endif
