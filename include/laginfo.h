#ifndef LAGINFO_H
#define LAGINFO_H

#include <iostream>

namespace video_analyzer {
    /**
     * @brief The LagInfo struct stores the information
     * about the lags in the video. Number of lags, maximum
     * delay of the lags and average delay of the lags
     */
    struct LagInfo {
      int num_lags;
      double max_lag;
      double avg_lag;
      friend std::ostream& operator<<(std::ostream& stream, LagInfo a) {
        stream << a.num_lags << "\t" << a.avg_lag << "\t" << a.max_lag;
      }
    };
}

#endif // LAGINFO_H

