#ifndef ETSII_TEST_H
#define ETSII_TEST_H

namespace etsii {

const int test_1_begin = 15607;
const int test_1_end = 33991;
const struct video_analyzer::ROI test_1_roi(342, 256, 573, 397);

const int test_2_frame = 31000;
const int test_2_characters = 23499;
const struct video_analyzer::ROI test_2_roi(64, 490, 780, 25);

const int test_3_begin = 44215;
const int test_3_end = 48127;
const struct video_analyzer::ROI test_3_roi(7, 242, 85, 34);

const int test_4_frame = 48227;
const int test_4_clicks = 1000;
const struct video_analyzer::ROI test_4_roi(2, 242, 84, 16);

const int test_5_begin = 55227;
const int test_5_end = 66244;
const struct video_analyzer::ROI test_5_roi(500, 548, 368, 48);


const struct video_analyzer::ROI test_5_roi_2(49, 119, 73, 17);
const struct video_analyzer::ROI test_5_roi_3(146, 300, 200, 50);

}

#endif // ETSII_TEST_H

