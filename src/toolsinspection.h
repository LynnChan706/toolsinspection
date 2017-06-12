#ifndef TOOLSINSPECTION_H
#define TOOLSINSPECTION_H

#include "toolsinspection_global.h"
#include <vector>
#include "opencv2/core/core.hpp"

using namespace cv;
class InspectionManage;

enum TOOL_RES
{
    TOOL_EXIST_ = 1,
    TOOL_NOT_EXIS_ = 2,
    TOOL_UNKNOWN_ = 3,
    ERR_NO_TEMPLATE_ = 4,
    ERR_INSPECT_IMG_ = 5
};

class TOOLSINSPECTIONLIBSHARED_EXPORT ToolsInspection
{
public:
	ToolsInspection();
	~ToolsInspection();
    void setDebugInfo(bool debugState);

    void setCheckStateParam(float thresholdValue);

    bool setTmplImageAndMarker(Mat tmplImage,
                               std::vector<Rect> markerList = std::vector<Rect>());

    bool setCurrentInspectImage(Mat inspectImage);

    int inspection(Rect toolRect, std::vector<Point2f> &resRect,float &resScore, Mat toolImage=Mat());

private:
    InspectionManage * _pManage;

};

#endif //TOOLSINSPECTION_H

