#ifndef INSPECTIONMANAGE_H
#define INSPECTIONMANAGE_H

#include <vector>
#include "opencv2/core/core.hpp"
#include "matcher.hpp"

using namespace cv;
class ChessMarker;
class CheckToolState;

class InspectionManage
{
public:
    InspectionManage();
    ~InspectionManage();

    bool setTmplImageAndMarker(Mat tmplImage,
                               std::vector<cv::Rect> markerList = std::vector<cv::Rect>());

    void setDebugInfo(bool debugState);

    void setCheckStateParam(float thresholdValue);

    bool setCurrentInspectImage(cv::Mat inspectImage);

    int inspection(Rect toolRect, std::vector<Point2f> & resRect, float &resScore, Mat toolImage);

private:

    bool getHomography(std::vector<cv::DMatch>& matches,
                       std::vector<cv::KeyPoint> & keypoints1,
                       std::vector<cv::KeyPoint> & keypoints2);

private:

    Mat _tmplImage;
    Mat _inspectImage;
    Mat _loctImage;
    Mat  _warpMat;
    float _stateThreshold;
    std::vector<cv::Rect> _markerList;
    ChessMarker * _pChessMaker;
    CheckToolState * _pCheckState;
};

#endif // INSPECTIONMANAGE_H
