#ifndef SENSOR_CAMERA_CLASS_H_
#define SENSOR_CAMERA_CLASS_H_

#include <iostream>     //cout
#include <memory>       //uiqueptr

#include "opencv2/opencv.hpp"

#include <sensor_base_class.hpp>

class sensor_camera_class : public sensor_base_class {

private:
    //! the opencv camera object
    std::unique_ptr<cv::VideoCapture> m_camera_ptr;

    int m_camera_port;
    //! the linux video port to be used

    //! during acquisition the new frame is stored together with a flag whether it is valid
    cv::Mat m_current_frame;
    bool m_current_frame_valid;

    //! default constructor not to be used
    sensor_camera_class();

public:

    sensor_camera_class(const address_class &address, const int video_port);
    ~sensor_camera_class();
    //sensor_state_type get_state();

    bool init_sensor();
    bool acquire_data();
    bool fetch_current_frame(cv::Mat &frame);
    bool create_sensor_message();
    bool queue_sensor_message();

    void set_sensor_type();
};

#endif
