//
// Created by kobus on 2017/04/06.
//

#pragma once


#include <opencv2/core/mat.hpp>
#include "../util/threads.h"
#include "imageStabKalman.h"

class cpuDsp
{
public:
    static void executeTiPipeline(cv::Mat& frame,
                                  cv::Mat& outputFrame,
                                  cv::Mat& originalFrame,
                                  TiDspParameters parameters,
                                  bool showComparisonWindows);
    static void eZoom(cv::Mat &frame, TiDspParameters params);
    static void startNuc(void);
    static void startStab(bool lock);
private:
    static bool nonUniformitiesGenerated;
    static bool getNucSample;
    static int currentNucSample;
    static const int nucSamples = 1000;
    static cv::Mat nucReferenceFrames[nucSamples];

    static void generateNonUniformities(cv::Mat& frame);
    static void equalizeHistogram(cv::Mat& mat);
    static void rgbToGrayScale(cv::Mat& frame);
    static void addNonUniformities(cv::Mat& frame);
    static void frameAverage(cv::Mat& frame);
    static void edgeEnhance(cv::Mat& frame, TiDspParameters params);
    static void sharpen(cv::Mat& frame);
    static void moveFrame(const cv::Mat &frame, const cv::Mat &dest, TiDspParameters params);
    static void spatialFilter(cv::Mat &frame);
    static void temporalFilter(cv::Mat &frame);
    static void generateSensorSensitivity(cv::Mat &mat);
    static void generate1PtSceneNucWithStab(void);
    static void generate1PtWithAveraging(void);
    static void applyNuc(cv::Mat& frame);
    static void stab(cv::Mat& frame);
};


