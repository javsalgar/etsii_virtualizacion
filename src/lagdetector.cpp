#include "lagdetector.h"
#include <limits>

using namespace video_analyzer;

LagDetector::~LagDetector()
{
}

LagDetector::LagDetector(const std::string &filename): LagDetector(std::make_shared<cv::VideoCapture>(filename))
{
    if (vc_ == NULL) {
        throw std::invalid_argument("Error opening video file");
    }
}

LagDetector::LagDetector(std::shared_ptr<cv::VideoCapture> vc)
{
    vc_ = vc;

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

bool LagDetector::compareTwoFrames(const cv::Mat &im1, const cv::Mat &im2)
{
    bool equal = true;

    for (int i = 0; i < im1.rows; i ++) {
       for (int j = 0; j < im1.cols; j ++) {
           for (int k = 0; k < im1.elemSize(); k ++) {
            if (im1.data[im1.step * i + j*im1.elemSize() + k] != im2.data[im2.step * i + j*im1.elemSize() + k]) {
                equal = false;
            }
           }
       }
    }

    return equal;
}

bool LagDetector::getLags(int begin_frame, int end_frame, const ROI &roi, LagInfo &lag_info)
{
    bool first_difference_found = false;

    int current_frame_number;
    int current_lag_duration = 0;
    int total_lag_duration = 0;
    int total_lags = 0;
    int max_lag_duration = INT32_MIN;

    vc_->set(CV_CAP_PROP_POS_FRAMES, (double)begin_frame);
    cv::Rect rect_roi(roi.x, roi.y, roi.width, roi.height);

    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    cv::Mat previous_reg;

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_AVI_RATIO) <= 1) {
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

                if (current_lag_duration > 0) {
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
    }

    lag_info.avg_lag = ((double)total_lag_duration/total_lags)/fps_;
    lag_info.max_lag = max_lag_duration/fps_;
    lag_info.num_lags = total_lags;

    return true;
}

