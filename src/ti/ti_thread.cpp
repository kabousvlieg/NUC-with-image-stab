//
// Created by kobus on 2016/01/28.`
//

#define TI_THREAD_CPP //Debugging

#include "ti_thread.h"
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

const bool showComparisonWindows = false;
const bool showOutputWindow = true;

/* TiDsp_thread class -------------------------------------------------------------------------------------------*/
TiDsp_thread::TiDsp_thread(boost::lockfree::spsc_queue<FromTiDspThread> &produce,
                           boost::lockfree::spsc_queue<ToTiDspThread> &consume)
        : produceQ(produce), consumeQ(consume)
{

}

void TiDsp_thread::run(void)
{
    try
    {
        if (showComparisonWindows)
        {
            cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
            cv::moveWindow("Original", 0, 0);
            cv::namedWindow("Difference", cv::WINDOW_AUTOSIZE);
            cv::moveWindow("Difference", 0, 600);
            cv::namedWindow("Histogram", cv::WINDOW_AUTOSIZE);
            cv::moveWindow("Histogram", 750, 600);
        }
        if (showOutputWindow)
        {
            cv::namedWindow("Enhanced", cv::WINDOW_AUTOSIZE);
            cv::moveWindow("Enhanced", 750, 0);
        }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        for (;;)
        {
            static int framePosition = 0;
            cv::Mat originalFrame, outputFrame;
            Camera_thread::frameMutex[framePosition].lock();
            if (!Camera_thread::frameProcessed[framePosition])
            {
                processFrame(Camera_thread::frame[framePosition], originalFrame, outputFrame);
                Camera_thread::frameProcessed[framePosition] = true;
                Camera_thread::frameMutex[framePosition].unlock();
                framePosition++;
                if (framePosition >= 3)
                    framePosition = 0;

                info.pipeLineFrameRate++;
                updateFrameRate();
            }
            else
            {
                Camera_thread::frameMutex[framePosition].unlock();
                boost::this_thread::yield();
            }


            ToTiDspThread TiMsg;
            if (!consumeQ.empty())
            {
                consumeQ.pop(TiMsg);
                handleGuiCommand(TiMsg);
            }

            std::this_thread::yield;
        }
#pragma clang diagnostic pop
	}
	catch (std::exception& e)
	{
		std::cout << "Caught exception:" << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch (std::exception* e)
	{
		std::cout << "Caught exception:" << std::endl;
		std::cout << e->what() << std::endl;
	}
}

void TiDsp_thread::processFrame(cv::Mat &frame, cv::Mat &originalFrame, cv::Mat &outputFrame)
{
#if USE_CUDA
    cudaDsp::executeTiPipeline(frame, originalFrame, params, showComparisonWindows);
#else
    cpuDsp::executeTiPipeline(frame, outputFrame, originalFrame, params, showComparisonWindows);
#endif

    if (!frame.empty())
    {
        //if (showComparisonWindows)
        {
            calculateHistogram(frame);
        }
        displayResults(originalFrame, outputFrame);
    }

}

void TiDsp_thread::updateFrameRate()
{
    static auto start = timeClock::getMs();
    auto now = timeClock::getMs();
    if (now - start > 1000)
    {
        produceQ.push(FromTiDspThread{
                .reason = FromTiDspReason::FrameRateUpdate,
                .info = info
        });
        info.pipeLineFrameRate = 0;
        start = now;
    }
}

void TiDsp_thread::displayResults(cv::Mat& originalFrame, cv::Mat& outputFrame)
{
    wxMutexGuiEnter();
    if (showOutputWindow)
    {
        imshow("Enhanced", outputFrame);
    }
    if (showComparisonWindows)
    {
        imshow("Original", originalFrame);
        cv::Mat diff;
        if ( (!originalFrame.empty()) && (!outputFrame.empty()) )
            cv::absdiff(originalFrame, outputFrame, diff);
        else
            outputFrame.copyTo(diff);
        imshow("Difference", diff);
    }
    wxMutexGuiLeave();
}

void TiDsp_thread::calculateHistogram(cv::Mat& frame)
{
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    cv::Mat hist;

    /// Compute the histograms:
    calcHist( &frame, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    cv::Mat histImage( hist_h, hist_w, CV_8UC3, cv::Scalar( 0,0,0) );

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, cv::Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
              cv::Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
              cv::Scalar( 255, 0, 0), 2, 8, 0  );
    }

    /// Display
    imshow("Histogram", histImage );
}

void TiDsp_thread::printMat(cv::Mat& mat)
{
    std::cout << "M = "<< std::endl << " "  << mat << std::endl << std::endl;
}

void TiDsp_thread::handleGuiCommand(ToTiDspThread TiMsg)
{
    params = TiMsg.params;

    if (TiMsg.reason == ToTiDspReason::NucSample)
    {
        cpuDsp::startNuc();
    }

    if (TiMsg.reason == ToTiDspReason::StabLock)
    {
        if (params.stabLockOn)
            cpuDsp::startStab(true);
        else
            cpuDsp::startStab(false);
    }
}
