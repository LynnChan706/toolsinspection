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


/*************************************************
Description:    //Set templates and marker areas
Input:          //tmplImage: template image(toolbox picture without tools)
                //markerList: some marker areas(3*3 Chessboard image in every areas)
                //If the number of maker areas is 0, \
                // we will use SIFT features to locate tools
Return:         //Set templates result
*************************************************/

bool ToolsInspection::setTmplImageAndMarker(Mat tmplImage, std::vector<Rect> markerList)
{
    return _pManage->setTmplImageAndMarker(tmplImage,markerList);
}

/*************************************************
Description:    //inspection tools exists
Input:          //inspectImage: inspectImage image(toolbox picture)
                //toolImage:Need to inspection tools pictue
                //toolRect:tool position in the template image
Output:         //resRect:tool position in the inspectImage
Return:         //Inspection result
*************************************************/

int ToolsInspection::inspection(Mat inspectImage, Mat toolImage,Rect toolRect,Rect & resRect)
{
    return _pManage->inspection(inspectImage,toolImage,toolRect,resRect);

}

