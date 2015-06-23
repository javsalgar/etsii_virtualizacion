#ifndef VIDEO_UTILS_H
#define VIDEO_UTILS_H

#include <memory>
#include <opencv2/opencv.hpp>

namespace video_analyzer {

    int getNumDigits(int num);
    int seekFrame(std::shared_ptr<cv::VideoCapture> ptr, int frame);

}



#endif // VIDEO_UTILS_H

