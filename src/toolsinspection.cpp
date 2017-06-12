/*
* @Author: Lynnchan
* @Date:   2017-05-11 20:13:14
* @Modified by: LynnChan
* @Last Modified time: 2017-05-11 21:45:40
*/

#include "toolsinspection.h"
#include "inspectionmanage.h"

ToolsInspection::ToolsInspection()
{
    _pManage = new InspectionManage();

}
ToolsInspection::~ToolsInspection()
{
    if(_pManage != NULL)
    {
        delete _pManage;
        _pManage = NULL;
    }
}
void ToolsInspection::setDebugInfo(bool debugState)
{
    _pManage->setDebugInfo(debugState);
}

void ToolsInspection::setCheckStateParam(float thresholdValue)
{
    _pManage->setCheckStateParam(thresholdValue);
}

bool ToolsInspection::setTmplImageAndMarker(Mat tmplImage, std::vector<Rect> markerList)
{
    return _pManage->setTmplImageAndMarker(tmplImage,markerList);
}


bool ToolsInspection::setCurrentInspectImage(Mat inspectImage)
{
    return _pManage->setCurrentInspectImage(inspectImage);
}


int ToolsInspection::inspection(Rect toolRect, std::vector<Point2f> &resRect, float &resScore, Mat toolImage)
{
    return _pManage->inspection( toolRect, resRect,resScore, toolImage);

}

