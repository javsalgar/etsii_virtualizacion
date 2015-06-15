#ifndef ETSII_TEST_H
#define ETSII_TEST_H

namespace etsii {

const int test_1_init = 12309;
const int test_1_end = 27071;
const struct video_analyzer::ROI test_1_roi(342, 256, 573, 397);

const int test_2_frame = 31000;
const int test_2_characters = 23499;
const struct video_analyzer::ROI test_2_roi(64, 490, 780, 25);

const int test_3_init = 35120;
const int test_3_end = 38368;
const struct video_analyzer::ROI test_3_roi(7, 242, 85, 34);

const int test_4_frame = 38400;
const int test_4_clicks = 1000;
const struct video_analyzer::ROI test_4_roi(8, 242, 84, 16);

const int test_5_begin = 44163;
const int test_5_end = 55563;
const struct video_analyzer::ROI test_5_roi(557, 563, 168, 34);


const struct video_analyzer::ROI test_5_roi_2(49, 119, 73, 17);

}

#endif // ETSII_TEST_H

