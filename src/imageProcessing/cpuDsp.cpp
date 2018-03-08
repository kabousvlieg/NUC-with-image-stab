//
// Created by kobus on 2017/04/06.
//

#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <list>
#include <deque>
#include <iomanip>
#include <cv.hpp>
#include "cpuDsp.h"
#include "stabilisation.h"
#include "imageStabKalman.h"

const int cpuDsp::nucSamples;
bool cpuDsp::nonUniformitiesGenerated = false;
cv::Mat cpuDsp::nucReferenceFrames[nucSamples];
bool cpuDsp::getNucSample = false;
int cpuDsp::currentNucSample = 0;

cv::Mat nucOffsetMap;

static cv::Mat nonUniformitiesGain;
static cv::Mat nonUniformitiesOffset;
cv::Mat pixelNoise;
cv::Mat pixelSensitivity;

cv::Mat averages1;
cv::Mat averages2;
cv::Mat test;

enum STABSTATE
{
    Restart,
    Running,
    Stop
};
STABSTATE stabState = Restart;
Tracker stabTracker;


void printMat(cv::Mat image)
{
    std::cout << "Mat:" << std::endl;
    for (int i = 0; i < image.cols; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
    }
    std::cout << std::endl;

    for (int i = 0; i < image.rows; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
        for (int j = 0; j < image.cols; j++)
        {
            std::cout << (image.at<int>(i, j) & 0xFF) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printMatFloat(cv::Mat image)
{
    std::cout << "Mat:" << std::endl;
    for (int i = 0; i < image.cols; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
    }
    std::cout << std::endl;

    for (int i = 0; i < image.rows; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
        for (int j = 0; j < image.cols; j++)
        {
            std::cout << image.at<double>(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printArray(double array[1280][720])
{
    std::cout << "Mat:" << std::endl;
    for (int i = 0; i < 1280; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 720; i++)
    {
        std::cout << "  " << std::setfill('0') << std::setw(5) << i << "  ";
        for (int j = 0; j < 1280; j++)
        {
            std::cout << ((int)(array[i][j])) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void cpuDsp::generateNonUniformities(cv::Mat& frame)
{
    const int colNoiseMax = 40;
    const int pixelNoiseMax = 5;

    std::vector<double> colRandomGain;
    std::vector<double> colRandomOffset;
    srand (time(NULL));
    //Generate a column based randomization that dominates to simulate thermal imager column nonuniformities
    for (int i = 0; i < frame.cols; i++)
    {
        double colNoiseGain = (double)(rand() % 1000) / 5000 + 0.9; //Random value between 0.9 and 1.1
        double colNoiseOffset = (double)(rand() % (colNoiseMax*2)) - colNoiseMax; //Random value between -30 and 29
        colRandomOffset.push_back(colNoiseOffset);
    }

    cv::Mat nonUniformitiesGain = cv::Mat(frame.rows, frame.cols, CV_64F, double(0));
    cv::Mat nonUniformitiesOffset = cv::Mat(frame.rows, frame.cols, CV_64F, double(0));
    pixelNoise = cv::Mat(frame.rows, frame.cols, CV_64F, double(0));

    for (int i = 0; i < frame.cols; i++)
    {
        double colNoise = colRandomOffset[i];
        for (int j = 0; j < frame.rows; j++)
        {
            double pixelOffsetNoise = (double)(rand() % (pixelNoiseMax*2)) - pixelNoiseMax; //Random value between -5 and 4
            pixelNoise.at<double>(j, i) = pixelOffsetNoise + colNoise;
        }
    }
}

void cpuDsp::generateSensorSensitivity(cv::Mat &frame)
{
    const double sensitivityMax = 1.0;
    const double sensitivityMin = 0.1;

    pixelSensitivity = cv::Mat(frame.rows, frame.cols, CV_64F, double(0));
    for (int x = 0; x < frame.cols; x++)
    {
        for (int y = 0; y < frame.rows; y++)
        {
            //Simulate a centroid with higher sensitivity at the center
            double radius = pow(abs(y - (frame.rows/2)), 2) + pow(abs(x - (frame.cols/2)), 2);
            double maxRadius = pow(frame.cols / 2, 2) + pow(frame.rows / 2, 2);
            double sensitivity = sensitivityMax - ((radius / maxRadius) * (sensitivityMax - sensitivityMin));
            pixelSensitivity.at<double>(y, x) = sensitivity;
        }
    }
}

void cpuDsp::executeTiPipeline(cv::Mat& frame,
                               cv::Mat& outputFrame,
                               cv::Mat& originalFrame,
                               TiDspParameters params,
                               bool showComparisonWindows)
{
    static bool showStabilisation = false;
    static int stabFrame = 0;

    if (!nonUniformitiesGenerated)
    {
        generateNonUniformities(frame);
        generateSensorSensitivity(frame);
        nonUniformitiesGenerated = true;

        cv::namedWindow("Compare1", cv::WINDOW_AUTOSIZE);
        cv::moveWindow("Compare1", 0, 0);
        cv::namedWindow("Compare2", cv::WINDOW_AUTOSIZE);
        cv::moveWindow("Compare2", 750, 600);

        averages1 = cv::Mat::zeros(cv::Size(nucReferenceFrames[0].cols, nucReferenceFrames[0].rows), CV_64FC1);
    }

    if (params.outputSelect == OutputSelect::Raw)
        frame.copyTo(outputFrame);

    cv::cvtColor(frame, frame, CV_BGR2GRAY);
    if (showComparisonWindows)
    {
        originalFrame = frame.clone();
    }
    if (params.outputSelect == OutputSelect::GrayScale)
        frame.copyTo(outputFrame);

    if (params.nonUniformityOn)
        addNonUniformities(frame);
    if (params.outputSelect == OutputSelect::NonUniformity)
        frame.copyTo(outputFrame);

    if (getNucSample)
    {
        frame.copyTo(cpuDsp::nucReferenceFrames[currentNucSample++]);
        frame.copyTo(outputFrame);
        if (currentNucSample >= nucSamples) {
            getNucSample = false;
            currentNucSample = 0;

//            stabTracker.processImages(cpuDsp::nucReferenceFrames, nucSamples);
//            generate1PtSceneNucWithStab();

            showStabilisation = false;
            stabFrame = 0;
        }
        else
            generate1PtWithAveraging();
        //return;
    }

    if (showStabilisation)
    {
        if (stabFrame >= nucSamples)
        {
            //showStabilisation = false;
            stabFrame = 0;
        }

        {
            nucReferenceFrames[stabFrame].copyTo(outputFrame);
            stabFrame += 1;
            usleep(500);
            return;
        }
    }

    if (params.nucOn)
        applyNuc(frame);
    if (params.outputSelect == OutputSelect::Nuc)
        frame.copyTo(outputFrame);
//
//    if (params.frameAverageOn)
//        frameAverage(frame);
//    if (params.outputSelect == OutputSelect::FrameAverage)
//        frame.copyTo(outputFrame);

//    if (params.temporalFilterOn)
//        temporalFilter(frame);
//    if (params.outputSelect == OutputSelect::TemporalFilter)
//        frame.copyTo(outputFrame);
//
    if (params.spatialFilterOn)
        spatialFilter(frame);
    if (params.outputSelect == OutputSelect::SpatialFilter)
        frame.copyTo(outputFrame);

    if (params.edgeEnhanceOn)
        edgeEnhance(frame, params);
    if (params.outputSelect == OutputSelect::EdgeEnhance)
        frame.copyTo(outputFrame);

    if (params.stabLockOn)
        stab(frame);
    if (params.outputSelect == OutputSelect::Stab)
        frame.copyTo(outputFrame);

    if (params.outputSelect == OutputSelect::Stab)
        frame.copyTo(outputFrame);

    if (params.eZoomOn)
    {
        eZoom(frame, params);
        if (showComparisonWindows)
        {
            eZoom(originalFrame, params);
        }
    }
    if (params.outputSelect == OutputSelect::Ezoom)
        frame.copyTo(outputFrame);

    if (params.histogramStretchOn)
        equalizeHistogram(frame);
    if (params.outputSelect == OutputSelect::HistogramStretch)
        frame.copyTo(outputFrame);
//
    if (params.outputSelect == OutputSelect::Colorize)
        frame.copyTo(outputFrame);

    return;
}

void cpuDsp::startNuc(void)
{
    getNucSample = true;
    currentNucSample = 0;
}



void cpuDsp::equalizeHistogram(cv::Mat& frame)
{
    std::vector<cv::Mat> channels;
    cv::Mat img_hist_equalized;

    equalizeHist(frame, frame); //equalize histogram on the 1st channel (Y)
}

void cpuDsp::rgbToGrayScale(cv::Mat& frame)
{
    cv::cvtColor(frame, frame, CV_BGR2GRAY);
}

void cpuDsp::addNonUniformities(cv::Mat& frame)
{
    cv::Mat pixels;
    frame.convertTo(pixels, CV_64F);
    //cv::multiply(pixels, pixelSensitivity, pixels);
    //cv::add(pixels, pixelNoise, pixels);
    //Histogram de-stretching
    //cv::divide(pixels, 5, pixels);
    //cv::add(pixels, 255 / 2, pixels);
    pixels.convertTo(frame, CV_8U);
}

void cpuDsp::frameAverage(cv::Mat& frame)
{
    static cv::Mat previousFrame;

    if (previousFrame.empty())
    {
        previousFrame = frame;
        return;
    }

    cv::Mat avg, diff;
    avg.create(frame.cols, frame.rows, CV_32FC1);
    cv::addWeighted(frame, 0.5, previousFrame, 0.5, 0, avg);
    previousFrame = frame;
    avg.convertTo(frame, CV_8U);
}

void cpuDsp::edgeEnhance(cv::Mat& frame, TiDspParameters params)
{
    switch (params.edgeEnhanceType)
    {
        case EdgeEnhanceType::Sharpen:
        {
            cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                     0,-1, 0,
                    -1, 5,-1,
                     0,-1, 0);

            filter2D(frame, frame, CV_32F, kernel);
        }

        case EdgeEnhanceType::Gaussian:
        {
            cv::Mat kernel = (cv::Mat_<float>(5,5) <<
                    -1,-1,-1,-1,-1,
                    -1, 2, 2, 2,-1,
                    -1, 2, 8, 2,-1,
                    -1, 2, 2, 2,-1,
                    -1,-1,-1,-1,-1) / 8.0;

            filter2D(frame, frame, CV_32F, kernel);
            break;
        }

        case EdgeEnhanceType::Unsharp_mask:
        {
            cv::Mat kernel = (cv::Mat_<float>(5,5) <<
                    1, 4,   6, 4, 1,
                    4,16,  24,16, 4,
                    6,24,-476,24, 6,
                    4,16,  24,16, 4,
                    1, 4,   6, 4, 1) / -256.0;

            filter2D(frame, frame, CV_32F, kernel);
            break;
        }

        default:
        {
            break;
        }
    }
    frame.convertTo(frame, CV_8U);
    convertScaleAbs(frame, frame);
}

void cpuDsp::eZoom(cv::Mat &frame, TiDspParameters params)
{
    cv::Mat dest;
    switch (params.ezoom)
    {
        case Ezoom::NoZoom:
            break;
        case Ezoom::x2:
            cv::pyrUp(frame, dest, cv::Size(frame.cols * 2, frame.rows * 2));
            moveFrame(frame, dest, params);
            break;
        case Ezoom::x4:
            cv::pyrUp(frame, dest, cv::Size(frame.cols * 2, frame.rows * 2));
            cv::pyrUp(dest, dest, cv::Size(dest.cols * 2, dest.rows * 2));
            moveFrame(frame, dest, params);
            break;
        case Ezoom::x8:
            cv::pyrUp(frame, dest, cv::Size(frame.cols * 2, frame.rows * 2));
            cv::pyrUp(dest, dest, cv::Size(dest.cols * 2, dest.rows * 2));
            cv::pyrUp(dest, dest, cv::Size(dest.cols * 2, dest.rows * 2));
            moveFrame(frame, dest, params);
            break;
    }

}

void cpuDsp::moveFrame(const cv::Mat &frame, const cv::Mat &dest, TiDspParameters params)
{
    double availableXPixels, availableYPixels;
    double xMove, yMove;

    availableXPixels = dest.cols - frame.cols;
    availableYPixels = dest.rows - frame.rows;
    xMove = params.horisontalOffset / 100.0;
    yMove = params.verticalOffset / 100.0;
    dest(cv::Rect(xMove * availableXPixels, yMove * availableYPixels, frame.cols, frame.rows)).copyTo(frame);
}

void cpuDsp::spatialFilter(cv::Mat &frame)
{
    //cv::fastNlMeansDenoisingColored(frame, frame, 2, 2, 7, 21);
    cv::fastNlMeansDenoising(frame, frame, 2, 5, 17);
}

void cpuDsp::temporalFilter(cv::Mat &frame)
{

}

void cpuDsp::sharpen(cv::Mat& frame)
{
    cv::Mat blurred; double sigma = 1, threshold = 5, amount = 1;
    GaussianBlur(frame, blurred, cv::Size(), sigma, sigma);
    cv::Mat lowContrastMask = cv::abs(frame - blurred) < threshold;
    cv::Mat sharpened = frame*(1+amount) + blurred*(-amount);
    frame.copyTo(frame, lowContrastMask);
}

void cpuDsp::generate1PtSceneNucWithStab(void)
{
    int goodSamples[1280][720] = {0};
    averages1 = cv::Mat::zeros(cv::Size(nucReferenceFrames[0].cols, nucReferenceFrames[0].rows), CV_64FC1);
    averages2 = cv::Mat::zeros(cv::Size(nucReferenceFrames[0].cols, nucReferenceFrames[0].rows), CV_64FC1);

    for (int i = 0; i < nucSamples / 2; i++)
    {
        //printMat(nucReferenceFrames[i]);
//        for (int j = 0; j < nucReferenceFrames[0].rows; j++)
//        {
//            for (int k = 0; k < nucReferenceFrames[0].cols; k++)
//            {
////                nucReferenceFrames[i].convertTo(nucReferenceFrames[i], CV_64F);
//                if (nucReferenceFrames[i].empty())
//                    continue;
//                //if ( ((nucReferenceFrames[i].at<int>(j, k) & 0xFF) > 0) /* &&
//                //     (nucReferenceFrames[i].at<double>(j, k) <= 255)*/ )
//                {
//                    goodSamples[j][k] += 1;
//                    averages[j][k] += (nucReferenceFrames[i]).at<double>(j, k);
//                }
//            }
//        }
        cv::add(nucReferenceFrames[i], averages1, averages1, cv::Mat(), CV_64FC1);
    }

    for (int i = nucSamples / 2; i < nucSamples; i++)
    {
        cv::add(nucReferenceFrames[i], averages2, averages2, cv::Mat(), CV_64FC1);
    }

    nucOffsetMap = cv::Mat::zeros(cv::Size(nucReferenceFrames[0].cols, nucReferenceFrames[0].rows), CV_64FC1);

    averages1 /= nucSamples / 2; //goodSamples[j][k];
    averages2 /= nucSamples / 2; //goodSamples[j][k];
    cv::Mat outputFrame;
    averages1.convertTo(outputFrame, CV_8UC1);
    cv::imshow("Compare1", outputFrame);

    averages2.convertTo(outputFrame, CV_8UC1);
    cv::imshow("Compare2", outputFrame);
    cv::subtract(averages1, averages2, nucOffsetMap, cv::Mat(), CV_64FC1);

    //std::cout << std::endl;
    //for (int j = 0; j < nucReferenceFrames[0].rows; j++)
    //{
        //for (int k = 0; k < nucReferenceFrames[0].cols; k++)
        //{
            //std::cout << goodSamples[j][k] << " ";
            //averages.at<double>(j, k) /= nucSamples; //goodSamples[j][k];
            //nucOffsetMap.at<double>(j, k) = (double)(nucReferenceFrames[0].at<int>(j, k) & 0xFF) - averages.at<double>(j, k);
        //}
        //std::cout << std::endl;
    //}
    std::cout << "Klaar" << std::endl;

//    printMatFloat(averages);
//    printMatFloat(nucOffsetMap);
}


void cpuDsp::generate1PtWithAveraging(void)
{
    cv::Mat movingAverage;

    if (currentNucSample == 1)
    {
        nucReferenceFrames[currentNucSample - 1].copyTo(averages1);
    }
    else
    {
        nucReferenceFrames[currentNucSample - 1].convertTo(movingAverage, CV_64FC1);
        movingAverage /= (currentNucSample);
        averages1 *= (currentNucSample - 1) / (currentNucSample);
        cv::add(movingAverage, averages1, averages1, cv::Mat(), CV_64FC1);
        //averages1 *= 1.5;
    }

    cv::Mat outputFrame;
    averages1.convertTo(outputFrame, CV_8UC1);
    cv::imshow("Compare1", outputFrame);

    averages1.copyTo(nucOffsetMap);
}

void cpuDsp::applyNuc(cv::Mat& frame)
{
    if ( (nucOffsetMap.rows != frame.rows) ||
         (nucOffsetMap.cols != frame.cols) )
    {
        return;
    }

    //cv::add(frame, nucOffsetMap, frame);
    //nucOffsetMap.copyTo(frame);
    //nucReferenceFrames[0].copyTo(frame);

//    averages.convertTo(frame, CV_8UC1);
//    nucOffsetMap.convertTo(frame, CV_8UC1);
    cv::subtract(frame, nucOffsetMap, frame, cv::Mat(), CV_8UC1);

//    frame.create(720, 1280, CV_8U);

//    for (int j = 0; j < frame.rows; j++) {
//        for (int k = 0; k < frame.cols; k++) {
//            //if (averages[j][k] < 255)
//                frame.at<unsigned char>(j, k) = (unsigned char)(averages[j][k]);
//            //else
//            //    frame.at<int>(j, k) = 255;
//        }
//    }

    //frame = cv::Mat(720, 1280, CV_32F, averages);
}

void cpuDsp::startStab(bool lock)
{
    if (lock)
        stabState = Restart;
    else
        stabState = Stop;
}

void cpuDsp::stab(cv::Mat &frame)
{
    switch (stabState)
    {
        case Restart: {
            stabTracker.start(frame);
            stabState = Running;
            break;
        }
        case Running: {
            stabTracker.processImage(frame);
            break;
        }
        case Stop:break;
    }
}


