#include <iostream>
#include "lagdetector.h"
#include "laginfo.h"
#include "roi.h"
#include "etsii_test.h"
#include "frameextractor.h"
#include "textextractor.h"
#include "videofpsmeasurer.h"

using namespace std;

extern char _binary_test1_init_png_start;
extern char _binary_test1_init_png_end;

extern char _binary_test1_init_png_size;

int main()
{

    std::shared_ptr<cv::VideoCapture> ptr2(new cv::VideoCapture("/home/javsalgar/Code/Videos experimento/salidausuario7 07_02_2015_03_01_55.avi"));
    std::shared_ptr<cv::VideoCapture> ptr(new cv::VideoCapture("/home/javsalgar/Code/Videos experimento/salidausuario7 07_02_2015_03_01_55.avi"));
//    std::shared_ptr<cv::VideoCapture> ptr(new cv::VideoCapture("/home/javsalgar/salidausuario1 06_15_2015_05_38_02.avi"));
    video_analyzer::FrameExtractor f_ext(ptr);
    video_analyzer::FrameExtractor f_ext2(ptr2);

    cv::Mat imgbuf(cv::Size(100, 100), CV_8UC3, &_binary_test1_init_png_start);

//    cv::Mat im1 = f_ext2.extractFrame(21500, etsii::test_1_end_frame_roi);

//    cv::Mat im1 = cv::imread("/home/javsalgar/Code/video_analyzer/frames/test1_end.png");

    cv::Mat im1 = cv::imdecode(imgbuf, CV_LOAD_IMAGE_COLOR);

    cv::namedWindow("test2");
    cv::imshow("test2", im1);
    cv::waitKey(0);
    cv::destroyWindow("test2");


//    std::vector<int> compression_params;

//    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
//    compression_params.push_back(0);

//    cv::imwrite("/home/javsalgar/test1_end.png", im1, compression_params);

//    int res = video_analyzer::seekFrame(ptr, im1, etsii::test_1_end_frame_roi);

//    if (res != -1) {
//        cv::namedWindow("test");
//        cv::imshow("test", f_ext.extractFrame(res));
//        cv::waitKey(0);
//    } else {
//        std::cout << "Not found!" << std::endl;
//    }

    return 0;
}

