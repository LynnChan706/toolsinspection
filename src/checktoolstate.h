#ifndef CHECKTOOLSTATE_H
#define CHECKTOOLSTATE_H

#include <opencv2/core/core.hpp>

using namespace cv;

class CheckToolState
{
public:
    CheckToolState();

    float getToolState(Mat tmplImg,Mat inspectImg);

};

#endif // CHECKTOOLSTATE_H
