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

    video_analyzer::FrameExtractor f("/home/javsalgar/ejemplo.avi");
    //f.extractToFolder(etsii::test_2_frame,etsii::test_2_frame + 30, "/home/javsalgar/lags/");

    l.getLags(etsii::test_1_init, etsii::test_1_end,
              etsii::test_1_roi, res);


    std::cout << "results:" << std::endl << res;

    video_analyzer::TextExtractor t_ext(f.extractFrame(etsii::test_2_frame));

    std::string text_res;

    if (t_ext.getText(etsii::test_2_roi, text_res))
    {
        std::cout << "Recemos para que funcione: " << text_res << std::endl;
    }
    return 0;
}

