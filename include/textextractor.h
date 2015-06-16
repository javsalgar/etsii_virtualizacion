#ifndef TEXTEXTRACTOR_H
#define TEXTEXTRACTOR_H

#include <opencv2/opencv.hpp>
#include "roi.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


namespace video_analyzer {

    class TextExtractor
    {
    public:

        /**
         * @brief TextExtractor
         * @param image
         */
        TextExtractor(const cv::Mat& image);

        /**
         * @brief getText
         * @param roi
         * @return
         */
        bool getText(const struct ROI roi, std::string &out_text, int threshold);

    private:

        /**
         * @brief image_
         */
        cv::Mat image_;
        tesseract::TessBaseAPI *api_;
        bool init_success_;
    };
}
#endif // TEXTEXTRACTOR_H
