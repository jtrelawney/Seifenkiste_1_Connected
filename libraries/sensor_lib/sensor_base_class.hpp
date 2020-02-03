#ifndef SENSOR_BASE_CLASS_H_
#define SENSOR_BASE_CLASS_H_

#include <iostream>
#include <memory>       //uiqueptr

#include <time_class.hpp>
#include <address_class.hpp>
#include <message_class.hpp>


/*
base class - basic functions

1. constructor init
2. init sensor - read parameter file and startup the device
3. acquire sensor data
4. create sensormessage
5. queue sensor message

*/

//const int SENSOR_DEBUG_LEVEL = 1;

//enum sensor_state_type {sensor_not_initialized, sensor_init_failed, sensor_ready, invalid_sensor_state};
//sensor_state_type sensor_state_;

//*
class sensor_base_class{

private:
    //! the address of the particular sensor, this should be a unique identifier so that messages can be routed
    address_class m_sensors_own_address;
    //! default constructor - not to be used
    sensor_base_class();

protected:
    //! statistics - for each sensor data acquistion increase this count
    unsigned int m_data_acquisition_count;
    //! keep the timestamp for the most recent data acquisition
    def_time_format m_data_acquisition_timestamp;

public:

    sensor_base_class(const address_class &address);
    virtual ~sensor_base_class();

    virtual address_class get_address() final;

    virtual bool acquire_data();
    virtual std::unique_ptr<message_class> create_sensor_message(const address_class &receiver_address)=0;
    //virtual message_class* create_sensor_message(const address_class &receiver_address)=0;
    //virtual bool queue_sensor_message();

};

#endif
