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
