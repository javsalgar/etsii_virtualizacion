#include <iostream>
#include "lagdetector.h"
#include "laginfo.h"
#include "roi.h"
#include "etsii_test.h"
#include "frameextractor.h"
#include "textextractor.h"

using namespace std;

int main()
{
    video_analyzer::LagDetector l("/home/javsalgar/ejemplo.avi");
    video_analyzer::LagInfo res;

    //video_analyzer::FrameExtractor f("/home/javsalgar/ejemplo.avi");
    video_analyzer::FrameExtractor f("/home/javsalgar/Documents/Dropbox/ETSII/Doctorado/Proy cloud vitualización etsii/Videos Test/AA144pText.mpg");
    //f.extractToFolder(0, 300, "/home/javsalgar/lags/");

    cv::namedWindow("test");
    cv::imshow("test", f.extractFrame(13));
   // cv::imwrite("/home/javsalgar/manuela.jpg", f.extractFrame(etsii::test_4_frame));
    cv::waitKey(0);

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

