#include <camera_message_class.hpp>

camera_message_class::camera_message_class(
    cv::Mat frame,
    address_class receiver_address,
    unsigned int id,
    def_time_format time_stamp):
        message_class(receiver_address, message_type_enum::T_camera_message, id, time_stamp),
        my_time_stamp(time_stamp),
        my_data(frame),
        my_data_valid(true)
{
    std::cout <<"camera message class constructor" << std::endl;
}

camera_message_class::camera_message_class(header_buffer_class &buffer):
        message_class(buffer),
        my_time_stamp(0),
        my_data(cv::Mat()),
        my_data_valid(false)
{
    std::cout <<"camera message class constructor with buffer" << std::endl;
}

unsigned int camera_message_class::get_data_size(){
    if (my_data_valid) return my_data.rows * my_data.cols * my_data.channels();
    return 0;
}

camera_message_class::~camera_message_class()
{
        std::cout <<"camera message class de - constructor" << std::endl;
}

void camera_message_class::print_meta_data(){
        message_class::print_meta_data();
        std::cout <<"my_time_stamp = " << my_time_stamp << std::endl;
        std::cout <<"my_data valid = " << my_data_valid << std::endl;
        std::cout <<"my_data (rows = " << my_data.rows << ", cols = " << my_data.cols << ", channels = "<< my_data.channels() << ", type = " << my_data.type() << " )" << std::endl;
        std::cout <<"my_data size = " << get_data_size() << std::endl;
        std::cout <<"my_data type = " << my_data.type() << std::endl;
}

buffer_info camera_message_class::get_data_buffer_info(){
        buffer_info b;
        if (my_data_valid) {
            b.set_info(get_data_size(),(char *)my_data.data);
        } else std::cout <<"camera_message_class::get_data_buffer_info call, but data object not initialized" << std::endl;
        return b;
}

unsigned int camera_message_class::populate_header_buffer_from_member_data()
{
        // first call the populate function of the base class
        unsigned int N = message_class::populate_header_buffer_from_member_data();
        std::cout <<"writing header buffer for derived class at N = " << N << std::endl;

        // then copy the own members into the buffer
        N+=set_buffer_data(my_time_stamp, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_data_length = get_data_size();
        N+=set_buffer_data(my_data_length, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_rows = my_data.rows;
        N+=set_buffer_data(my_rows, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_cols = my_data.cols;
        N+=set_buffer_data(my_cols, N);
        std::cout <<"N = " << N << std::endl;
        int my_channels = my_data.channels();
        N+=set_buffer_data(my_channels, N);
        std::cout <<"N = " << N << std::endl;
        int my_data_type = my_data.type();
        //std::cout <<"Type = " << my_data.type() << " , " << my_data_type << std::endl;
        N+=set_buffer_data(my_data_type, N);
        std::cout <<"N = " << N << std::endl;
        print_header_buffer_content();
        return N;
}

unsigned int camera_message_class::populate_member_data_from_buffer(){
        // first call the populate function of the base class
        unsigned int N = populate_member_data(); //buffer
        std::cout <<"reading header buffer for derived class at N = " << N << std::endl;

        // then copy the buffer to own members and extract the data parameters
        N+=get_buffer_data(my_time_stamp, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_data_length;
        N+=get_buffer_data(my_data_length, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_rows;
        N+=get_buffer_data(my_rows, N);
        std::cout <<"N = " << N << std::endl;
        unsigned int my_cols;
        N+=get_buffer_data(my_cols, N);
        std::cout <<"N = " << N << std::endl;
        int my_channels;
        N+=get_buffer_data(my_channels, N);
        std::cout <<"N = " << N << std::endl;
        int my_data_type;
        N+=get_buffer_data(my_data_type, N);
        std::cout <<"N = " << N << std::endl;

        bool check_data_params_valid = (my_rows>0) && (my_cols>0);
        if (check_data_params_valid) {
            my_data = cv::Mat(my_rows, my_cols, my_data_type);
            int new_channels = my_data.channels();
            // if channel test is ok then Mat is valid, else something is wrong
            if (my_channels == new_channels) {
                my_data_valid = true;
            } else {
                std::cout << "cv mat construction : channel mismatch, orig = " << my_channels << " , new = " << new_channels << std::endl;
                assert(new_channels == my_channels);
            }
        } else std::cout << "cvmat params < 0 for rows/cols" << std::endl;
        print_header_buffer_content();
        return N;
}

// this prepares the data object so that the data can be received and written there
void camera_message_class::init_data_object_from_buffer_info()
{
        std::cout <<"initializing cv::mat of size = " << my_data.rows * my_data.cols << std::endl;
        exit(0);
}

cv::Mat camera_message_class::extract_current_frame(){
    return my_data;
}
