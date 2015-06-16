#include "textextractor.h"

using namespace video_analyzer;


TextExtractor::TextExtractor(const cv::Mat &image) : image_(image)
{
    api_ = new tesseract::TessBaseAPI();

    if (api_->Init(NULL, "eng")) {
        init_success_ = false;
    } else {
        init_success_ = true;
    }

}

bool TextExtractor::getText(const ROI roi, std::string& out_text, int threshold)
{
    if (init_success_) {
        cv::Rect rect_roi(roi.x, roi.y, roi.width, roi.height);
        cv::Mat region_image = image_(rect_roi);

        cv::Mat gray;
        cv::cvtColor(region_image, gray, CV_BGR2GRAY);
        cv::Mat binary;
        cv::threshold(gray, binary, threshold, 255, 0);

        api_->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
        api_->SetImage((uchar*)binary.data, binary.cols, binary.rows, 1, binary.cols);

        char* res_text = api_->GetUTF8Text();

        out_text.clear();
        out_text.append(res_text);
    }

    return init_success_;
}


