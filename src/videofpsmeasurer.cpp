#include "videofpsmeasurer.h"
#include "textextractor.h"
#include <sstream>

using namespace video_analyzer;


VideoFPSMeasurer::VideoFPSMeasurer(const std::string &filename):
    VideoFPSMeasurer(std::make_shared<cv::VideoCapture>(filename))
{
    if (vc_ == NULL) {
        throw std::invalid_argument("Error opening video file");
    }
}

VideoFPSMeasurer::VideoFPSMeasurer(std::shared_ptr<cv::VideoCapture> vc)
{
    vc_ = vc;
}

bool VideoFPSMeasurer::measureFPS(int begin_frame, int end_frame, FPSInfo &fps_res, int theoretical_fps, const ROI &roi, int threshold)
{
    int current_frame_number;
    int video_frame_number;
    int previous_video_frame_number;
    int first_frame;
    int missed_frames = 0;
    bool res = true;
    bool first = true;

    vc_->set(CV_CAP_PROP_POS_FRAMES, (double)begin_frame);
    current_frame_number = vc_->get(CV_CAP_PROP_POS_FRAMES);

    while (current_frame_number != end_frame &&
           vc_->get(CV_CAP_PROP_POS_AVI_RATIO) <= 1) {
        cv::Mat image;
        std::string fps_text;
        *vc_ >> image;
        TextExtractor t_ext(image);

        t_ext.getText(roi, fps_text, threshold);
        std::string orig = fps_text;

        std::replace(fps_text.begin(), fps_text.end(), 'O', '0');
        std::replace(fps_text.begin(), fps_text.end(), 'e', '0');
        std::replace(fps_text.begin(), fps_text.end(), 'E', '3');
        std::replace(fps_text.begin(), fps_text.end(), 'T', '7');
        std::replace(fps_text.begin(), fps_text.end(), 'G', '0');
        std::replace(fps_text.begin(), fps_text.end(), ')', ' ');
        std::replace(fps_text.begin(), fps_text.end(), ':', '1');
        fps_text[4] = ' ';

        std::stringstream i_str(fps_text);
        i_str >> video_frame_number;

        //std::cout << video_frame_number << std::endl;

        if (!first && video_frame_number < previous_video_frame_number) {
            std::cerr << "ERROR!! " << "Frame : " << current_frame_number <<   ", Prev: " << previous_video_frame_number <<
                         " " <<  orig << " " << fps_text << " : " << video_frame_number << std::endl;

        } else {

            if (first) {
                first_frame = video_frame_number;
                first = false;
            } else {
                int aux = video_frame_number - previous_video_frame_number;
                if (aux > 1) {
                    missed_frames += aux;
                }
            }
            previous_video_frame_number = video_frame_number;
        }

        current_frame_number++;
    }

    fps_res.missed_frames = missed_frames;
    fps_res.total_frames = video_frame_number - first_frame;
    fps_res.fps = ((double)theoretical_fps *
                   (fps_res.total_frames - fps_res.missed_frames))/fps_res.total_frames;

    return res;
}
