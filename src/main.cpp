#include <iostream>
#include "lagdetector.h"
#include "laginfo.h"
#include "roi.h"
#include "etsii_test.h"
#include "frameextractor.h"
#include "textextractor.h"
#include "videofpsmeasurer.h"

using namespace std;

int main()
{

    std::shared_ptr<cv::VideoCapture> ptr2(new cv::VideoCapture("/home/javsalgar/salidausuario10 06_22_2015_01_09_02.avi"));
    std::shared_ptr<cv::VideoCapture> ptr(new cv::VideoCapture("/home/javsalgar/salidausuario1 06_15_2015_05_02_13.avi"));
    video_analyzer::FrameExtractor f_ext(ptr);
    video_analyzer::FrameExtractor f_ext2(ptr2);

//    cv::Mat im1 = f_ext2.extractFrame(24990, etsii::test_2_frame_roi);

    cv::Mat im1 = cv::imread("/home/javsalgar/lossless2.png");

    cv::namedWindow("test2");
    cv::imshow("test2", im1);
    cv::waitKey(0);
    cv::destroyWindow("test2");


//    std::vector<int> compression_params;

//    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
//    compression_params.push_back(0);

//    cv::imwrite("/home/javsalgar/lossless2.png", im1, compression_params);

    int res = video_analyzer::seekFrame(ptr, im1, etsii::test_2_frame_roi);

    if (res != -1) {
        cv::namedWindow("test");
        cv::imshow("test", f_ext.extractFrame(res));
        cv::waitKey(0);
    }

    return 0;
}

