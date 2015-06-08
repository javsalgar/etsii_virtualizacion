#include <iostream>
#include "lagdetector.h"
#include "laginfo.h"
#include "roi.h"
#include "etsii_test.h"

using namespace std;

int main()
{
    video_analyzer::LagDetector l("/home/javsalgar/ejemplo.avi");
    video_analyzer::LagInfo res;

    l.getLags(etsii::test_1_init, etsii::test_1_end,
              etsii::test_1_roi, res);


    return 0;
}

