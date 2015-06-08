#ifndef LAGDETECTOR_H
#define LAGDETECTOR_H

#include "opencv2/opencv.hpp"
#include "laginfo.h"
#include "roi.h"
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
         * @brief Analyzes lag information in the video
         * @param begin_frame Starting frame
         * @param end_frame Ending frame
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(int begin_frame, int end_frame, struct LagInfo& lag_info);

        /**
         * @brief Analyzes lag information in the video
         * @param begin_frame Starting frame
         * @param end_frame Ending frame
         * @param roi Region of interest
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(int begin_frame, int end_frame, const struct ROI& roi, struct LagInfo& lag_info);

        /**
         * @brief Analyzes lag information in the video
         * @param roi Region of interest
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(const struct ROI& roi, struct LagInfo& lag_info);

        /**
         * @brief Analyzes lag information in the video
         * @param lag_info Lag information to be written
         * @return Whether the processing was done successfully
         */
        bool getLags(struct LagInfo& lag_info);

        /**
         * @brief compareTwoFrames checks if two frames are equal
         * @param im1 First image
         * @param im2 Second image
         * @return true if the images are the same
         */
        bool compareTwoFrames(const cv::Mat& im1, const cv::Mat& im2);

    private:

        /**
         * @brief Pointer to OpenCV Video capturer
         */
        cv::VideoCapture *vc_;

        /**
         * @brief Video's frames per second
         */
        double fps_;
    };
}
#endif // LAGDETECTOR_H
