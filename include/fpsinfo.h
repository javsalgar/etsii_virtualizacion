#ifndef FPSINFO_H
#define FPSINFO_H

namespace video_analyzer {
    struct FPSInfo {
        double fps;
        int missed_frames;
        int total_frames;

        friend std::ostream& operator<<(std::ostream& stream, FPSInfo a) {
          stream << a.fps << "\t" << a.missed_frames << "\t" << a.total_frames;
        }
    };
}

#endif // FPSINFO_H

