#ifndef CHECKTOOLSTATE_H
#define CHECKTOOLSTATE_H

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace cv;

class CheckToolState
{
public:
    CheckToolState();

    float getToolState(Mat tmplImg,Mat inspectImg);

    bool adaptiveBrightness(Mat tmplImg,Mat inspectImg,Mat &resImg);

private:
   cv::Ptr<cv::FeatureDetector>  _detector;

};

#endif // CHECKTOOLSTATE_H
