#ifndef ROI_H
#define ROI_H

namespace video_analyzer {

    /**
     * @brief The ROI struct determines the region of interest
     * to analyze. The (x, y) coordinates refer to the upper left
     * corner of the ROI rectangle.
     */
    struct ROI {
        ROI(int x_, int y_, int width_, int height_):
            x(x_), y(y_), width(width_), height(height_) {}
        int x;
        int y;
        int width;
        int height;
    };

}

#endif // ROI_H

