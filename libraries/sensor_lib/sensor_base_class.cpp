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
}

address_class sensor_base_class::get_address(){
    return m_sensors_own_address;
}

bool sensor_base_class::acquire_data(){
   return false;
}

std::unique_ptr<message_class> sensor_base_class::create_sensor_message(const address_class &receiver_address){
	return std::unique_ptr<message_class> (nullptr);
}
/*
message_class* sensor_base_class::create_sensor_message(const address_class &receiver_address){
	message_class* message = nullptr;
    return message;
}
*/
/*
bool sensor_base_class:: queue_sensor_message(){
    return false;
}
*/

//sensor_state_type sensor_base_class::get_state(){ return sensor_state_; }
