#include <opencv2/opencv.hpp>


bool send_frame(cv::Mat &frame){
    cv::imshow("usb_camera", frame);
    if(cv::waitKey(30) >= 0) return false;
    return true;
}

int main(int, char**)
{
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    cv::namedWindow("usb_camera",1);

    for(;;)
    {
        cv::Mat frame;
        cap >> frame;
        if (!send_frame(frame)) break;
    }

    return 0;
}
