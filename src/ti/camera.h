//
// Created by kobus on 2017/09/19.
//

#pragma once


using namespace std; //gpu requires for compilation
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "../util/threads.h"

class Camera_thread : public threads
{
public:
    Camera_thread(boost::lockfree::spsc_queue<FromTiCameraThread> &produce,
                    boost::lockfree::spsc_queue<ToTiCameraThread> &consume);
    void run(void) override;

    //Circular buffer implementation without copies (more efficient)
    static std::mutex frameMutex[3];
    static cv::Mat frame[3];
    static bool frameProcessed[3];

private:
    boost::lockfree::spsc_queue<FromTiCameraThread> &produceQ;
    boost::lockfree::spsc_queue<ToTiCameraThread> &consumeQ;
    TiCameraInfo info;

    void updateFrameRate();
    void getFeedType(cv::VideoCapture &cap);
};
