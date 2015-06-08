#include "lagdetector.h"

using namespace video_analyzer;

LagDetector::~LagDetector()
{
    if (vc_ != NULL) {
        delete vc_;
    }
}

LagDetector::LagDetector(const std::string &filename)
{
    vc_ = new cv::VideoCapture(filename);

    if (vc_ != NULL) {
        fps_ = vc_->get(CV_CAP_PROP_FPS);
    }
}

bool LagDetector::getLags(int begin_frame, int end_frame, LagInfo &lag_info)
{
    struct ROI roi(0, 0, vc_->get(CV_CAP_PROP_FRAME_WIDTH),
                   vc_->get(CV_CAP_PROP_FRAME_HEIGHT));
    return getLags(begin_frame, end_frame, roi, lag_info);
}

bool LagDetector::getLags(const ROI &roi, LagInfo &lag_info)
{
    return getLags(0,-1, roi, lag_info);
}

bool LagDetector::getLags(LagInfo &lag_info)
{
    struct ROI roi(0, 0, vc_->get(CV_CAP_PROP_FRAME_WIDTH),
                   vc_->get(CV_CAP_PROP_FRAME_HEIGHT));
    return getLags(0,-1, roi, lag_info);

}

bool LagDetector::getLags(int begin_frame, int end_frame, const ROI &roi, LagInfo &lag_info)
{
    vc_->set(CV_CAP_PROP_POS_FRAMES, (double)begin_frame);

    cv::namedWindow("Test",1);

    int current_frame_number;

    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_AVI_RATIO) <= 1) {
        std::cout << "Frame " << current_frame_number << std::endl;
        cv::Mat frame;
        *vc_ >> frame;
        cv::imshow("Test", frame);
        if(cv::waitKey(30) >= 0) break;
        current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);
    }

    return true;
}

