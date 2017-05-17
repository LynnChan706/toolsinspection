#include "inspectionmanage.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algcommon.hpp"
#include "chessmarker.h"

InspectionManage::InspectionManage()
{
    _pChessMaker=new ChessMarker();
}

InspectionManage::~InspectionManage()
{
    if(_pChessMaker != NULL)
    {
        delete _pChessMaker;
        _pChessMaker = NULL;
    }
}

bool InspectionManage::setTmplImageAndMarker(Mat tmplImage,
                                             std::vector<Rect> markerList)
{

    return false;
}


int InspectionManage::inspection(Mat inspectImage, Mat toolImage,
                                 Rect toolRect, Rect &resRect)
{
    //    cv::Rect
        int x=5;
        FUN_INFO("alg"<<"123"<<x);
        LOG_OUT(LOG_DEBUG,"a=%d",10);
        Mat testImage = cv::imread("timg2.jpg");
        cv::Size markerSize = cv::Size(3,3);
        if(_pChessMaker != NULL && testImage.size().width>0)
        {
            _pChessMaker->getMakerPointList(testImage,markerSize);
        }

        std::cout<<"hello"<<std::endl;
        return 0;
}
