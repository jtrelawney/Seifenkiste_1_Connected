#ifndef _MESSAGE_CAMERA_CLASS
#define _MESSAGE_CAMERA_CLASS

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <message_class.h>

class camera_message_class:public message_class{

private:
    cv::Mat m_image;
    int m_cols, m_rows, m_channels, m_type;

    // message recipient uses cv::Mat (cv::Size(frame.cols,frame.rows),frame.type(), frame.data); to reconstruct the image into a cv::mat
    // -> cols, rows, type to reconstruct
    // and also channels, to calculate the size of the tcp data segment = rows*cols*channels


public:
    camera_message_class();                 /// creates empty message with unique message id
    camera_message_class(cv::Mat &image);   /// creates message with text

    ~camera_message_class();

    // move paradigm
    //message_class(message_class& other) = delete;
    //message_class& operator= (message_class& other) = delete;
    //message_class(message_class&& other) = default;
    //message_class& operator= (message_class&& other) = default;

};

#endif
