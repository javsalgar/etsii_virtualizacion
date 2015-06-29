#ifndef LAGDETECTOR_H
#define LAGDETECTOR_H

#include "opencv2/opencv.hpp"
#include "laginfo.h"
#include "roi.h"
#include <memory>

namespace video_analyzer {
    /**
     * @brief The LagDetector class. Created to detect lags in video streams
     */
    class LagDetector
    {

    public:

        ~LagDetector();

        /**
         * @brief LagDetector
         * @param filename
         */

        LagDetector(const std::string& filename);

        /**
         * @brief LagDetector
         * @param vc pointer to a cv::VideoCapture object
         */
        LagDetector(std::shared_ptr<cv::VideoCapture> vc);

        /**
         * @brief Analyzes lag information in the video
         * @param begin_frame Starting frame
         * @param end_frame Ending frame
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(int begin_frame, int end_frame, struct LagInfo& lag_info, int lag_threshold);

        /**
         * @brief Analyzes lag information in the video
         * @param begin_frame Starting frame
         * @param end_frame Ending frame
         * @param roi Region of interest
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(int begin_frame, int end_frame, const struct ROI& roi, struct LagInfo& lag_info, int lag_threshold);

        /**
         * @brief Analyzes lag information in the video
         * @param roi Region of interest
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(const struct ROI& roi, struct LagInfo& lag_info, int lag_threshold);

        /**
         * @brief Analyzes lag information in the video
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(struct LagInfo& lag_info, int lag_threshold);


    private:

        /**
         * @brief Pointer to OpenCV Video capturer
         */
        std::shared_ptr<cv::VideoCapture> vc_;

        /**
         * @brief Video's frames per second
         */
        double fps_;

    };
}
#endif // LAGDETECTOR_H
