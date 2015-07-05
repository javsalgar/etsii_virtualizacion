#include "lagdetector.h"
#include <limits>
#include "video_utils.h"

using namespace video_analyzer;

LagDetector::~LagDetector()
{
}

LagDetector::LagDetector(const std::string &filename, double fps): LagDetector(std::make_shared<cv::VideoCapture>(filename), fps)
{
    if (vc_ == NULL) {
        throw std::invalid_argument("Error opening video file");
    }
}

LagDetector::LagDetector(std::shared_ptr<cv::VideoCapture> vc, double fps): fps_(fps)
{
    vc_ = vc;
}

bool LagDetector::getLags(int begin_frame, int end_frame, LagInfo &lag_info, int lag_threshold)
{
    struct ROI roi(0, 0, vc_->get(CV_CAP_PROP_FRAME_WIDTH),
                   vc_->get(CV_CAP_PROP_FRAME_HEIGHT));
    return getLags(begin_frame, end_frame, roi, lag_info, lag_threshold);
}

bool LagDetector::getLags(const ROI &roi, LagInfo &lag_info, int lag_threshold)
{
    return getLags(0,-1, roi, lag_info, lag_threshold);
}

bool LagDetector::getLags(LagInfo &lag_info, int lag_threshold)
{
    struct ROI roi(0, 0, vc_->get(CV_CAP_PROP_FRAME_WIDTH),
                   vc_->get(CV_CAP_PROP_FRAME_HEIGHT));
    return getLags(0,-1, roi, lag_info, lag_threshold);

}


bool LagDetector::getLags(int begin_frame, int end_frame, const ROI &roi, LagInfo &lag_info, int lag_threshold)
{
    bool first_difference_found = false;

    int current_frame_number;
    int current_lag_duration = 0;
    int total_lag_duration = 0;
    int total_lags = 0;
    int max_lag_duration = INT32_MIN;

    seekFrame(vc_, begin_frame);

    cv::Rect rect_roi(roi.x, roi.y, roi.width, roi.height);

    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    cv::Mat previous_reg;

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_FRAMES) == current_frame_number) {
        cv::Mat frame;
        *vc_ >> frame;
        cv::Mat reg = frame(rect_roi);

        if (previous_reg.empty()) {
            previous_reg = reg;
        }

        if (compareTwoFrames(reg, previous_reg)) {
            if (first_difference_found) {
                current_lag_duration++;
            }
        } else {

            if (first_difference_found) {

                if (current_lag_duration > lag_threshold) {
                    total_lags++;
                    total_lag_duration+= current_lag_duration;
                    if (current_lag_duration >= max_lag_duration) {
                        max_lag_duration = current_lag_duration;
                    }
                }

            }

            current_lag_duration = 0;

            first_difference_found = true;
        }

        current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);
        previous_reg = reg;

        if (current_frame_number >= end_frame) {
            cv::imwrite("/home/javsalgar/discordia.jpg", frame);
        }
    }

    lag_info.avg_lag = ((double)total_lag_duration/total_lags)/fps_;
    lag_info.max_lag = max_lag_duration/fps_;
    lag_info.num_lags = total_lags;

    return true;
}

