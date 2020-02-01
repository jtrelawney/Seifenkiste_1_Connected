#include "opencv2/opencv.hpp"
#include <address_class.hpp>
#include <sensor_camera_class.hpp>
//#include <camera_message_class.hpp>

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

int main()
{
    cv::namedWindow("usb_camera",1);
    address_class sensor_address = get_camera_sensor_address();
    sensor_camera_class *camera = new sensor_camera_class(sensor_address,0);
    address_class receiver_address = get_receiver_address();

	for(;;)
    {
        cv::Mat frame;
        camera->acquire_data();

        if (camera->fetch_current_frame(frame) == true ) {
            cv::imshow("usb_camera", frame);
            camera->create_sensor_message(receiver_address);
            //camera->queue_sensor_message();
        }
        else std::cout << "frame invalid" << std::endl;

        if( cv::waitKey(30) >= 0) break;
    }

    delete camera;

    return 0;
}
