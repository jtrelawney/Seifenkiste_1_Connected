#include <message_class.hpp>
#include <sensor_camera_class.hpp>
#include <opencv2/opencv.hpp>

address_class define_camera_sensor_type(){
    address_class::Platform_def platform = address_class::Platform_def::rpi;
    address_class::Sensor_def sensor = address_class::Sensor_def::camera1;
    address_class::Process_def process = address_class::Process_def::undefined;
    return address_class(platform,sensor,process);
}

int main(int, char**){

        address_class sensor_address = define_camera_sensor_type();
        sensor_camera_class *camera = new sensor_camera_class(sensor_address,0);

        cv::Mat frame;
        cv::namedWindow("usb_camera",1);

        for(;;)
        {
            camera->acquire_data();
            if (camera->fetch_current_frame(frame)){
                imshow("usb_camera", frame);
            }

            if(cv::waitKey(30) >= 0) break;
        }

        delete camera;

        return 0;
}
/*
cv::VideoCapture cap(0);

cv::Mat get_frame(){
    cv::Mat frame;
    cap >> frame;
    return frame;
}

int main(int, char**)
{
    if(!cap.isOpened())
        return -1;

    cv::namedWindow("usb_camera",1);
    for(;;)
    {
        cv::Mat frame = get_frame();

        imshow("usb_camera", frame);
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}
*/
