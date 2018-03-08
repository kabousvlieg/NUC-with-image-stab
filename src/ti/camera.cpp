//
// Created by kobus on 2017/09/19.
//


#define CAMERA_THREAD_CPP //Debugging

#include "camera.h"
#include "../util/timeClock.h"
#include "../imageProcessing/cpuDsp.h"
#include "../imageProcessing/cudaDsp.h"

#include <wx/wx.h>

#include <boost/thread.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/date_time.hpp>
#include <boost/circular_buffer.hpp>
#include <mutex>
#include <thread>

std::mutex Camera_thread::frameMutex[3];
cv::Mat Camera_thread::frame[3];
bool Camera_thread::frameProcessed[3] = {true, true, true};

/* TiCamera_thread class ---------------------------------------------------------------------------------*/
Camera_thread::Camera_thread(boost::lockfree::spsc_queue<FromTiCameraThread> &produce,
                             boost::lockfree::spsc_queue<ToTiCameraThread> &consume)
        : produceQ{produce}, consumeQ{consume}
{
    std::cout << "OpenCV version : " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << std::endl;
#if not USE_CUDA
    std::cout << "Cuda not being used" << std::endl;
#endif
}

void Camera_thread::run(void)
{
    //Laptop webcam
    cv::VideoCapture cap;
    cap.open(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);

    //Tegra webcam:
    //cv::VideoCapture cap("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)1024,format=(string)I420, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink"); //open the default camera

    if (!cap.isOpened())
    {
        std::cout << "Could not initialize capturing...\n";
        return;
    }
    getFeedType(cap);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    for (;;)
    {
        static int framePosition = 0;
        frameMutex[framePosition].lock();
        if (frameProcessed[framePosition])
        {

            cap >> frame[framePosition];
            if (frame[framePosition].empty())
            {
                std::cout << "Frame empty, should not happen" << std::endl;
                frameMutex[framePosition].unlock();
                boost::this_thread::yield();
            }
            else
            {
                frameProcessed[framePosition] = false;
                frameMutex[framePosition].unlock();
                info.frameRate++;
                updateFrameRate();

                framePosition++;
                if (framePosition >= 3)
                    framePosition = 0;
            }
        }
        else
        {
            frameMutex[framePosition].unlock();
        }

        ToTiCameraThread TiMsg;
        if (!consumeQ.empty())
        {
            consumeQ.pop(TiMsg);
            //handleGuiCommand(TiMsg);
        }
        std::this_thread::yield;
    }
#pragma clang diagnostic pop
}

void Camera_thread::updateFrameRate()
{
    static auto start = timeClock::getMs();
    auto now = timeClock::getMs();
    if (now - start > 1000)
    {
        produceQ.push(FromTiCameraThread{
                .reason = FromTiCameraReason::FrameRateUpdate,
                .info = info
        });
        info.frameRate = 0;
        start = now;
    }
}

void Camera_thread::getFeedType(cv::VideoCapture &cap)
{
    cv::Mat frame;
    cap >> frame;
    while (frame.empty())
        cap >> frame;
    auto bitDepth = frame.depth();
    switch (bitDepth)
    {
        case CV_8U :
            info.bitDepth = 8;
            break;
        case CV_8S :
            info.bitDepth = 8;
            break;
        case CV_16U:
            info.bitDepth = 16;
            break;
        case CV_16S:
            info.bitDepth = 16;
            break;
        case CV_32S:
            info.bitDepth = 32;
            break;
        case CV_32F:
            info.bitDepth = 32;
            break;
        case CV_64F:
            info.bitDepth = 64;
            break;
        default:
            info.bitDepth = 0;
            break;
    }
    info.colourSpace = frame.channels();
    info.horisontalPixels = frame.cols;
    info.verticalPixels = frame.rows;
}
