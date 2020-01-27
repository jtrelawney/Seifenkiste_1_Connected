#include <opencv2/opencv.hpp>

using namespace cv;

VideoCapture cap(0);

cv::Mat get_frame(){
    cv::Mat frame;
    cap >> frame;
    return frame;
}

int main(int, char**)
{
    if(!cap.isOpened())
        return -1;

    namedWindow("usb_camera",1);
    for(;;)
    {
        Mat frame = get_frame();
            
        imshow("usb_camera", frame);
        if(waitKey(30) >= 0) break;
    }
    return 0;
}
