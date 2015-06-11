#ifndef FPSINFO_H
#define FPSINFO_H

namespace video_analyzer {
    struct FPSInfo {
        double fps;
        int missed_frames;
        int total_frames;
    };
}

#endif // FPSINFO_H

