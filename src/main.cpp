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
    video_analyzer::LagDetector l("/home/javsalgar/Code/ejemplo.avi");
    video_analyzer::LagInfo res;
    std::shared_ptr<cv::VideoCapture> ptr(new cv::VideoCapture("/home/javsalgar/Code/ejemplo.avi"));

    //video_analyzer::FrameExtractor f("/home/javsalgar/Documents/Dropbox/ETSII/Doctorado/Proy cloud vitualización etsii/Videos Test/AA144pText.mpg");
    //f.extractToFolder(0, 300, "/home/javsalgar/lags/");

    video_analyzer::VideoFPSMeasurer v_measure(ptr);

    struct video_analyzer::FPSInfo fps_res;

    v_measure.measureFPS(etsii::test_5_begin,
                         etsii::test_5_end, fps_res,
                         25, etsii::test_5_roi);

//    l.getLags(etsii::test_1_init, etsii::test_1_end,
//              etsii::test_1_roi, res);


//    std::cout << "results:" << std::endl << res << std::endl;

//    video_analyzer::TextExtractor t_ext(f.extractFrame(etsii::test_2_frame));

//    std::string text_res;

//    if (t_ext.getText(etsii::test_2_roi, text_res))
//    {
//        int characters;
//        std::stringstream istr(text_res);
//        istr.ignore(256, ' ');
//        istr.ignore(256,' ');
//        istr >> characters;
//        std::cout << characters << " characters" << std::endl;
//    }
    return 0;
}

