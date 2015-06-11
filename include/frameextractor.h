#ifndef FRAMEEXTRACTOR_H
#define FRAMEEXTRACTOR_H
#include <memory>
#include "opencv2/opencv.hpp"
#include "roi.h"
namespace video_analyzer {
    /**
     * @brief The FrameExtractor class is responsible of extracting frames from a video
     * and storing them in the filesystem
     */
    class FrameExtractor
    {
    public:

        /**
         * @brief FrameExtractor
         * @param filename
         */
        FrameExtractor(const std::string& filename);

        /**
         * @brief FrameExtractor
         * @param vc
         */
        FrameExtractor(std::shared_ptr<cv::VideoCapture> vc);

        ~FrameExtractor();

        /**
         * @brief extractToFolder extracts frames to a path
         * @param begin_frame initial frame
         * @param end_frame ending frame
         * @param path storing path
         * @return whether the extraction was successful
         */
        bool extractToFolder(int begin_frame, int end_frame, const std::string& path);

        /**
         * @brief extractToFolder extracts frames to a path
         * @param path storing path
         * @return whether the extraction was successful
         */
        bool extractToFolder(const std::string& path);

        /**
         * @brief extractFrame extracts a frame in the cv::Mat format
         * @param frame number
         * @return cv::Mat structure with the required information
         */
        cv::Mat extractFrame(int frame);

        cv::Mat extractFrame(int frame, const struct ROI& roi);

    private:

        /**
         * @brief Pointer to OpenCV Video capturer
         */
        std::shared_ptr<cv::VideoCapture> vc_;
    };
}
#endif // FRAMEEXTRACTOR_H
