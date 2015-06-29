#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "roi.h"

namespace video_analyzer {

    int getNumDigits(int num);
    int seekFrame(std::shared_ptr<cv::VideoCapture> ptr, int frame);
    int seekFrame(std::shared_ptr<cv::VideoCapture> ptr, cv::Mat img, struct ROI roi);
    int seekFrame(std::shared_ptr<cv::VideoCapture> ptr, cv::Mat img);

    /**
     * @brief compareTwoFrames checks if two frames are equal
     * @param im1 First image
     * @param im2 Second image
     * @return true if the images are the same
     */
    bool compareTwoFrames(const cv::Mat& im1, const cv::Mat& im2);

}



#endif // VIDEO_UTILS_H

