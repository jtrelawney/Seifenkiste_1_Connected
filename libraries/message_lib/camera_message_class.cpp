#include <camera_message_class.hpp>

camera_message_class::camera_message_class(
    cv::Mat frame,
    address_class receiver_address,
    unsigned int id,
    def_time_format stamp):
        message_class(receiver_address, message_type_enum::T_camera_message, id),
        my_data_length(frame.rows*frame.cols),
        my_time_stamp(stamp),
        my_data(frame)
{
    std::cout <<"camera message class constructor" << std::endl;
}

camera_message_class::camera_message_class(header_buffer_class &buffer):
        message_class(buffer),
        my_data_length(0),
        my_time_stamp(0)
{
    std::cout <<"camera message class constructor with buffer" << std::endl;
}

camera_message_class::~camera_message_class()
{
        std::cout <<"camera message class de - constructor" << std::endl;
}

void camera_message_class::print_meta_data(){
        message_class::print_meta_data();
        std::cout <<"my_data_length = " << my_data_length << std::endl;
        std::cout <<"my_time_stamp = " << my_time_stamp << std::endl;
        std::cout <<"my_data = " << my_data.rows*my_data.cols << std::endl;
}

buffer_info camera_message_class::get_data_buffer_info(){
        buffer_info b;
        b.set_info(my_data.rows * my_data.cols,(char *)my_data.data);
        return b;
}

unsigned int camera_message_class::populate_header_buffer_from_member_data()
{
        // first call the populate function of the base class
        unsigned int N = message_class::populate_header_buffer_from_member_data();
        std::cout <<"writing header buffer for derived class at N = " << N << std::endl;
        // then copy the own members into the buffer
        N+=set_buffer_data(my_data_length, N);
        std::cout <<"N = " << N << std::endl;
        N+=set_buffer_data(my_time_stamp, N);
        std::cout <<"N = " << N << std::endl;
        print_header_buffer_content();
        return N;
}

unsigned int camera_message_class::populate_member_data_from_buffer(){ //header_buffer_class &buffer
        // first call the populate function of the base class
        unsigned int N = populate_member_data(); //buffer
        std::cout <<"reading header buffer for derived class at N = " << N << std::endl;
        // then copy the buffer to own members
        N+=get_buffer_data(my_data_length, N);
        std::cout <<"N = " << N << std::endl;
        N+=get_buffer_data(my_time_stamp, N);
        std::cout <<"N = " << N << std::endl;
        print_header_buffer_content();
        return N;
}

// this prepares the data object so that the data can be received and written there
void camera_message_class::init_data_object_from_buffer_info()
{
        std::cout <<"initializing cv::mat of size = " << my_data.rows * my_data.cols << std::endl;
        exit(0);
}
