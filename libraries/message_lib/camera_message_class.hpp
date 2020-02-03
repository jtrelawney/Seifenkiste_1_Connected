#include <iostream>
#include "opencv2/opencv.hpp"

#include <time_class.hpp>
#include <message_class.hpp>

// example for deriving a message from the base class
// 1. constructors need to call the corresponding base class constructors and then set the own members
// 2. virtual function for populate_header_buffer_from_member_data():
//      first call the base class method to transfer those members into the buffer
//      then transfer the own members
// 3. virtual function for populate_member_data_from_buffer():
//      first call the base class method to transfer the buffer to those members
//      then transfer the own members

class camera_message_class:public message_class{
private:
    def_time_format my_time_stamp;
    cv::Mat my_data;
    bool my_data_valid;

protected:
    unsigned int get_data_size();
public:
    camera_message_class(cv::Mat frame, address_class receiver_address, unsigned int id, def_time_format stamp);
    ~camera_message_class();

    //* creates an empty message, populates the members from the buffer, and creates an empty image frame of appropriate size
    camera_message_class(header_buffer_class &buffer);
    // this prepares the data object so that the data can be received and written there
    void init_data_object_from_buffer_info();

    void print_meta_data();
    buffer_info get_data_buffer_info();

    unsigned int populate_header_buffer_from_member_data();
    unsigned int populate_member_data_from_buffer();

    cv::Mat extract_current_frame();
};
