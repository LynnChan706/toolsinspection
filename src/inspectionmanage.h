#ifndef INSPECTIONMANAGE_H
#define INSPECTIONMANAGE_H

#include <vector>
#include "opencv2/core/core.hpp"

using namespace cv;
class ChessMarker;

class InspectionManage
{
public:
    InspectionManage();
    ~InspectionManage();

    bool setTmplImageAndMarker(cv::Mat tmplImage,
                               std::vector<cv::Rect> markerList = std::vector<cv::Rect>());

    int inspection(cv::Mat inspectImage, cv::Mat toolImage,
                   cv::Rect toolRect, Rect &resRect);

private:
    ChessMarker * _pChessMaker;
};

#endif // INSPECTIONMANAGE_H
