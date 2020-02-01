#include <sensor_camera_class.hpp>

//sensor_state_type sensor_camera_class::get_state(){ return sensor_state_; }


sensor_camera_class::sensor_camera_class(const address_class &address, const int video_port):
    sensor_base_class(address),
    m_camera_ptr(nullptr),
    m_camera_port(video_port),
    m_current_frame_valid(false)
{
    std::cout << "sensor_camera_class : constructor" << std::endl;
    //cv::VideoCapture test = cv::VideoCapture(m_camera_port);
    //cv::VideoCapture *test = new cv::VideoCapture(m_camera_port);
    m_camera_ptr = std::unique_ptr<cv::VideoCapture> ( new cv::VideoCapture(m_camera_port) );

    // ensure camera init was succesful
    bool isopen = m_camera_ptr -> isOpened();
    if ( !( isopen ) ) {
        std::cout << "camera_sensor_class : init_sensor : issue opening the camera" << "\n";
        assert(isopen == true);
    }
}

sensor_camera_class::~sensor_camera_class(){
    std::cout << "camera_sensor_class : de - structor" << std::endl;
}

bool sensor_camera_class::init_sensor(){
    std::cout << "camera_sensor_class : init_sensor : not valid, camera init happens in constructor" << "\n";
    return false;
}


bool sensor_camera_class::fetch_current_frame(cv::Mat &frame){
    if (m_current_frame_valid == false) return false;
    frame = m_current_frame;
    return true;
}

bool sensor_camera_class::acquire_data(){

    // to maintain the frame state, assume failure and clear when success
    m_current_frame_valid = false;
    bool result = false;

    // grab a frame from the camera and get a timeetamp immediately
    result = m_camera_ptr -> grab();
    m_data_acquisition_timestamp = get_time_stamp_ns();

    if (result == false) {
        std::cout << "camera_sensor_class : acquire_data : issue grabing a frame" << std::endl;
        return false;
    }

    // retrieve the frame from the camera
    result = m_camera_ptr -> retrieve(m_current_frame);
    if (result == false) {
        std::cout << "camera_sensor_class : acquire_data : issue retrieving the frame" << "\n";
        return false;
    }

    // at this point the frame is valid
    m_data_acquisition_count ++;
    m_current_frame_valid = true;
    //std::cout << "camera_sensor_class : acquire_data : frame ready" << std::endl;
    return true;
}

/*
message_class sensor_camera_class::create_sensor_message(){
    return false;
}
*/
camera_message_class* sensor_camera_class::create_sensor_message(const address_class &receiver_address){
    camera_message_class* message = new camera_message_class(m_current_frame, receiver_address, m_data_acquisition_count, m_data_acquisition_timestamp);
    return message;
}

/*
bool sensor_camera_class:: queue_sensor_message(){
    return false;
}
*/
