#ifndef LAGINFO_H
#define LAGINFO_H

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
    };
}

#endif // LAGINFO_H

