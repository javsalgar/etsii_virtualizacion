#include "frameextractor.h"
#include <iostream>
#include <iomanip>
#include "video_utils.h"

using namespace video_analyzer;

FrameExtractor::FrameExtractor(const std::string &filename): FrameExtractor(std::make_shared<cv::VideoCapture>(filename))
{
    if (vc_ == NULL) {
        throw std::invalid_argument("Error opening video file");
    }
}

FrameExtractor::FrameExtractor(std::shared_ptr<cv::VideoCapture> vc)
{
    vc_ = vc;
}

FrameExtractor::~FrameExtractor()
{
}

bool FrameExtractor::extractToFolder(const std::string &path)
{
    return extractToFolder(0,-1, path);
}

cv::Mat FrameExtractor::extractFrame(int frame)
{
    vc_->set(CV_CAP_PROP_POS_FRAMES, (double)frame);
    cv::Mat res;

    *vc_ >> res;

    return res;
}

cv::Mat FrameExtractor::extractFrame(int frame, const struct ROI &roi)
{
    cv::Mat res = extractFrame(frame);
    cv::Rect rect_roi(roi.x, roi.y, roi.width, roi.height);

    return res(rect_roi);
}

bool FrameExtractor::extractToFolder(int begin_frame, int end_frame, const std::string &path)
{
    int current_frame_number;
    bool res = true;

    int digits = getNumDigits(end_frame);

    //vc_->set(CV_CAP_PROP_POS_FRAMES, (double)begin_frame);
    seekFrame(vc_, begin_frame);

    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_FRAMES) == current_frame_number) {
        cv::Mat image;
        std::stringstream filename;
        *vc_ >> image;
        filename << path << "frame-" << std::setfill('0') << std::setw(digits) <<
                    (current_frame_number) << ".jpg";
        if (!cv::imwrite(filename.str(), image)) {
            res = false;
        }
        current_frame_number++;

        std::cout << "CURRENT " << current_frame_number << " OPENCV " <<
                     vc_->get(CV_CAP_PROP_POS_FRAMES) << " RATIO " <<
                     vc_->get(CV_CAP_PROP_POS_AVI_RATIO) <<
                     std::endl ;
    }

    return res;
}
