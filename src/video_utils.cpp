#include "video_utils.h"

int video_analyzer::getNumDigits(int num)
{
    int res = 1;

    while (num % (int) pow(10,res) != num) {
        res++;
    }

    return res;
}

int video_analyzer::seekFrame(std::shared_ptr<cv::VideoCapture> ptr, int frame)
{
    int current_frame_number = ptr->get(CV_CAP_PROP_POS_FRAMES);

    if (current_frame_number > frame) {
        ptr->set(CV_CAP_PROP_POS_FRAMES, (double) 1);
        current_frame_number = 1;
    }

    while (current_frame_number != frame &&
           ptr->get(CV_CAP_PROP_POS_FRAMES) == current_frame_number) {
        cv::Mat m;

        *ptr >> m;

        current_frame_number++;
    }

    return ptr->get(CV_CAP_PROP_POS_FRAMES);
}


int video_analyzer::seekFrame(std::shared_ptr<cv::VideoCapture> ptr, cv::Mat img, struct ROI roi)
{
    int current_frame_number = ptr->get(CV_CAP_PROP_POS_FRAMES);

    cv::Rect rect_roi(roi.x, roi.y, roi.width, roi.height);

    cv::Mat gray_in;
    cv::cvtColor(img, gray_in, CV_BGR2GRAY);
    cv::Mat binary_in;
    cv::threshold(gray_in, binary_in, 200, 255, 0);

    while (ptr->get(CV_CAP_PROP_POS_FRAMES) == current_frame_number) {
        cv::Mat m;

        *ptr >> m;

        if (!m.empty()) {

            cv::Mat m_rec = m(rect_roi);

            cv::Mat gray_rec;
            cv::cvtColor(m_rec, gray_rec, CV_BGR2GRAY);
            cv::Mat binary_rec;
            cv::threshold(gray_rec, binary_rec, 200, 255, 0);

            if (compareTwoFrames(binary_in, binary_rec) == true) {
                return current_frame_number;
            }
        }

        current_frame_number++;
    }

    return -1;
}


int video_analyzer::seekFrame(std::shared_ptr<cv::VideoCapture> ptr, cv::Mat img)
{
    struct ROI roi(0, 0, ptr->get(CV_CAP_PROP_FRAME_WIDTH),
                  ptr->get(CV_CAP_PROP_FRAME_HEIGHT));

   return seekFrame(ptr, img, roi);
}


bool video_analyzer::compareTwoFrames(const cv::Mat &im1, const cv::Mat &im2)
{
    bool equal = true;

    for (int i = 0; i < im1.rows; i ++) {
       for (int j = 0; j < im1.cols; j ++) {
           for (int k = 0; k < im1.elemSize(); k ++) {
            if (im1.data[im1.step * i + j*im1.elemSize() + k] !=
                    im2.data[im2.step * i + j*im1.elemSize() + k]) {
                equal = false;
            }
           }
       }
    }

    return equal;
}
