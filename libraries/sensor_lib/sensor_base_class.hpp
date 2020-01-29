#ifndef SENSOR_BASE_CLASS_H_
#define SENSOR_BASE_CLASS_H_

#include <iostream>
#include <time_class.hpp>
#include <address_class.hpp>

/*
base class - basic functions

1. constructor init
2. init sensor - read parameter file and startup the device
3. acquire sensor data
4. create sensormessage
5. queue sensor message

*/

const int SENSOR_DEBUG_LEVEL = 1;

//enum sensor_state_type {sensor_not_initialized, sensor_init_failed, sensor_ready, invalid_sensor_state};
//sensor_state_type sensor_state_;

//*
class sensor_base_class{

private:

    address_class m_sensors_own_address;
    //! the address of the particular sensor, this should be a unique identifier so that messages can be routed
    //int sensor_debug_level_;

    //! default constructor not to be used
    sensor_base_class();

protected:
    unsigned int m_data_acquisition_count;
    def_time_format most_recent_acquisition_time_;

public:

    sensor_base_class(const address_class &address);
    virtual ~sensor_base_class();


    virtual bool init_sensor()=0;
    virtual bool acquire_data();
    virtual bool create_sensor_message();
    virtual bool queue_sensor_message();

    //virtual sensor_state_type get_state();
    virtual address_class get_address() final;
};

#endif
