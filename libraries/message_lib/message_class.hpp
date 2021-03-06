#ifndef MESSAGE_CLASS_H_
#define MESSAGE_CLASS_H_

#include <iostream>
#include <time_class.hpp>
#include <address_class.hpp>
#include <header_buffer.hpp>

enum class message_type_enum : unsigned char
{
    T_camera_message    = 0x01,
    T_time_sync_message = 0x02,
    T_other_message    = 0xfe,
    T_undefined_message = 0xff,
};

std::ostream& operator << (std::ostream& os, const message_type_enum& message_type);

class message_class:protected header_buffer_class{

private:

    //! receiver address
    address_class m_receiver_address;
    //! message type so that the proper object type can be reconstructed from buffer
    message_type_enum m_message_type;
    //! unique id for each message, best based on global counter
    unsigned int m_id;
    //! timestamp when the data was observed
    def_time_format m_sensor_time_stamp;

    //! default constructor not to be used
    message_class() = delete;

protected:
    //! copies the message class members into the buffer
    unsigned int populate_header_buffer();
    //! copies the buffer into the message class members
    unsigned int populate_member_data();//header_buffer_class &buffer);

public:
    //! construct with the private member settings
    message_class(address_class address,message_type_enum mtype, unsigned int mid,def_time_format time_stamp);
    //! construct with a given buffer (eg. after tcp header receiver)
    message_class(header_buffer_class &buffer);
    //! default de-structor
    ~message_class();

    //! populates the header buffer with the message class members by calling populate_header_buffer()
    virtual unsigned int populate_header_buffer_from_member_data();
    //! populates the message class members from the buffer by calling populate_member_data()
    virtual unsigned int populate_member_data_from_buffer(header_buffer_class &buffer);

    //! reads out the message type
    message_type_enum get_message_type();
    //! reads out the receiver address
    address_class get_receiver_address();

    //! prints the message class member data
    virtual void print_meta_data();

    //! reads the header buffer parameters, since message class owns buffer this is final
    virtual buffer_info get_header_buffer_info() final;

    //! reads the data buffer parameters, since the derived class owns the data, this is pure virtual
    virtual buffer_info get_data_buffer_info()=0;
};

#endif
