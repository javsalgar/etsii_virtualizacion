#include "frameextractor.h"

using namespace video_analyzer;

FrameExtractor::FrameExtractor(const std::string &filename)
{
    vc_ = new cv::VideoCapture(filename);
}

FrameExtractor::~FrameExtractor()
{
    if (vc_ != NULL) {
        delete vc_;
    }
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

    cv::namedWindow("test");
    cv::imshow("test", res);
    cv::waitKey(0);

    return res;
}

bool FrameExtractor::extractToFolder(int begin_frame, int end_frame, const std::string &path)
{
    int current_frame_number;
    bool res = true;

    vc_->set(CV_CAP_PROP_POS_FRAMES, (double)begin_frame);
    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_AVI_RATIO) <= 1) {
        cv::Mat image;
        std::stringstream filename;
        *vc_ >> image;
        filename << path << "frame-" << (current_frame_number) << ".jpg";
        if (!cv::imwrite(filename.str(), image)) {
            res = false;
        }
        current_frame_number++;
    }

    return res;
}
