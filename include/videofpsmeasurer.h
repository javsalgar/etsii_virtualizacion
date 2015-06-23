#ifndef VIDEOFPSMEASURER_H
#define VIDEOFPSMEASURER_H

#include <opencv2/opencv.hpp>
#include <memory>
#include "roi.h"
#include "fpsinfo.h"

namespace video_analyzer {

    class VideoFPSMeasurer
    {
    public:
        VideoFPSMeasurer(const std::string& filename);
        VideoFPSMeasurer(std::shared_ptr<cv::VideoCapture> vc);

        bool measureFPS(int begin_frame, int end_frame, FPSInfo &fps_res, int fps, const struct ROI& roi, int threshold);
        void fixText(std::string& fps_text);
    private:
        std::shared_ptr<cv::VideoCapture> vc_;
    };

}
#endif // VIDEOFPSMEASURER_H
