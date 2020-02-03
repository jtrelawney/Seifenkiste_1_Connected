#include "opencv2/opencv.hpp"
#include <address_class.hpp>
#include <sensor_camera_class.hpp>
#include <memory> // smart and unique ptr etc
//#include <camera_message_class.hpp>

//* example for using the camera sensor class to read a cvmat frame
//* creating a message from it, simulating a transfer via tcp
//* creating a new message from the header data and finally
//* unwrapping and displaying the frame

using Cam_message_ptr  = std::unique_ptr<camera_message_class>;

address_class get_camera_sensor_address(){
    address_class::Platform_def platform = address_class::Platform_def::rpi;;
    address_class::Sensor_def sensor = address_class::Sensor_def::camera1;
    address_class::Process_def process = address_class::Process_def::undefined;
    return address_class(platform,sensor,process);
}

address_class get_receiver_address(){
    address_class::Platform_def platform = address_class::Platform_def::pc;;
    address_class::Sensor_def sensor = address_class::Sensor_def::undefined_sensor;
    address_class::Process_def process = address_class::Process_def::cockpit;
    return address_class(platform,sensor,process);
}

// global camera
sensor_camera_class *camera = new sensor_camera_class(get_camera_sensor_address(),0);

Cam_message_ptr read_camera_and_create_message(){
    cv::Mat frame;
    camera->acquire_data();
    if (camera->fetch_current_frame(frame) == true ) {
        //std::unique_ptr<camera_message_class> camera_message = camera->create_sensor_message(get_receiver_address());
        Cam_message_ptr camera_message = camera->get_sensor_message(get_receiver_address());
        return camera_message;
        //message = camera->create_sensor_message(get_receiver_address());
    }
    else std::cout << "frame invalid" << std::endl;

    return std::unique_ptr<camera_message_class> (nullptr);
}

camera_message_class *receive_tcp_message(Cam_message_ptr message_to_send){
    //return message_to_send.get();

    camera_message_class *sensor_message = message_to_send.get();
    sensor_message -> populate_header_buffer_from_member_data();
    buffer_info source_bi = sensor_message -> get_header_buffer_info();
    header_buffer_class header_buffer;
    buffer_info target_bi = header_buffer.get_header_buffer_info();
    std::cout << "source length = " << source_bi.buffer_length << " , target_length = " << target_bi.buffer_length << std::endl;

    assert(source_bi.buffer_length == target_bi.buffer_length);
    for (unsigned int i=0; i<source_bi.buffer_length; i++){
        *(target_bi.buffer_pointer + i) = *(source_bi.buffer_pointer + i);
    }
    camera_message_class *cam_message = new camera_message_class(header_buffer);
    // populate the message from the buffer and create the data_object
    cam_message -> populate_member_data_from_buffer();
    source_bi = sensor_message ->get_data_buffer_info();
    target_bi = cam_message->get_data_buffer_info();

    std::cout << "source length = " << source_bi.buffer_length << " , target_length = " << target_bi.buffer_length << std::endl;

    // copy the data
    assert(source_bi.buffer_length == target_bi.buffer_length);
    for (unsigned int i=0; i<source_bi.buffer_length; i++){
        *(target_bi.buffer_pointer + i) = *(source_bi.buffer_pointer + i);
    }

    //cam_message -> init_data_object_from_buffer_info();
    cam_message -> print_meta_data();
    //camera_message_class* message_received = message_to_send; // for testing readons return the orig
    //return message_received;
    return cam_message;
}

cv::Mat receive_frame(Cam_message_ptr message_to_send){
    camera_message_class *received_message = message_to_send.get();
    return received_message->extract_current_frame();
}

int main()
{
    // camera object is created globaly
    cv::namedWindow("usb_camera",1);
    //address_class sensor_address = get_camera_sensor_address();
    address_class receiver_address = get_receiver_address();

	for(;;)
    {
        Cam_message_ptr sensor_message_ptr = read_camera_and_create_message();
        camera_message_class *received_message = receive_tcp_message(std::move(sensor_message_ptr));
        if (received_message) {
            cv::Mat frame = received_message->extract_current_frame();
            cv::imshow("usb_camera", frame);
            address_class extracted_address = received_message->get_receiver_address();
            bool correct_address = (extracted_address == receiver_address);
            if (!correct_address) std::cout << "wrong receiver address " << extracted_address << std::endl;
        }
        if( cv::waitKey(30) >= 0) break;
    }

    if (camera) delete camera;

    return 0;
}
