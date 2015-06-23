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
    std::shared_ptr<cv::VideoCapture> ptr(new cv::VideoCapture("/home/javsalgar/test.avi"));

    video_analyzer::FrameExtractor f_ext(ptr);

    f_ext.extractToFolder(300, 800, "/home/javsalgar/Frames/");
    f_ext.extractToFolder(300, 800, "/home/javsalgar/Frames/");

    std::cout << "Frame numbers: " << ptr->get(CV_CAP_PROP_FRAME_COUNT) << std::endl;

    return 0;
}

