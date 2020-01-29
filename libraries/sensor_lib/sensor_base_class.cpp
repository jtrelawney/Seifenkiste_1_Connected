#include <sensor_base_class.hpp>

/**
    the sensor base class is a virtual base class which defines the common members
    and shared functions, as well as the virtual functions each sensor should implement
*/

sensor_base_class::sensor_base_class(const address_class &address):
            //sensor_state_(sensor_state_type::sensor_not_initialized),
			m_sensors_own_address(address),
            m_data_acquisition_count(0),
			m_data_acquisition_timestamp(0)
			//sensor_debug_level_(SENSOR_DEBUG_LEVEL)
{
    //std::cout << "sensor_base_class : constructor : debuglevel = " << sensor_debug_level_ << "\n";
    std::cout << "sensor_base_class : constructor" << std::endl;
    std::cout << "address = " << m_sensors_own_address << std::endl;
}

sensor_base_class::~sensor_base_class(){
    std::cout << "sensor_base_class : de - structor" << std::endl;
   //sensor_state_ = sensor_state_type::sensor_not_initialized;
}



address_class sensor_base_class::get_address(){
    //std::cout << "sensor_base_class : set_sensor_type " << sensor_type << "\n";
    return m_sensors_own_address;
}

/*
int sensor_base_class::init_sensor(){
    return -1;
}
*/
bool sensor_base_class::acquire_data(){
   return false;
}

bool sensor_base_class::create_sensor_message(){
    return false;
}

bool sensor_base_class:: queue_sensor_message(){
    return false;
}


//sensor_state_type sensor_base_class::get_state(){ return sensor_state_; }
