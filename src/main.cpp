#include <iostream>
#include "lagdetector.h"
#include "laginfo.h"
using namespace std;

int main()
{
    video_analyzer::LagDetector l("/home/javsalgar/ejemplo.avi");
    video_analyzer::LagInfo res;

    l.getLags(4000,4300,res);
    l.getLags(16000,16500,res);
    l.getLags(1000,1500,res);

    return 0;
}

