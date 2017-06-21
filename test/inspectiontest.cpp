#include "toolsinspection.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <iostream>

#define DEBUG_OUT  std::cout<<"[TEST OUT]: "<<__FUNCTION__<<" "<< __LINE__

int main(int argc, char *argv[])
{

    ToolsInspection inspect;
    Mat inspectImage;
    Mat tmplImage;
    Mat toolImage;
    DEBUG_OUT<<" statr inspect!"<<std::endl;
    if(argc==2)
    {
        String str=argv[1];
        inspectImage = cv::imread(str);
        if(inspectImage.empty())
        {
            DEBUG_OUT<<" Image error!"<<std::endl;
            inspectImage = cv::imread("test2.jpg");
        }
    }
    else
    {
        inspectImage = cv::imread("2017-06-19_19_03_34_927.bmp");
    }
    tmplImage = cv::imread("tmp.bmp");
    toolImage = cv::imread("tmpltool.jpg");

//    cv::cvtColor(tmplImage,tmplImage,cv::COLOR_BGR2GRAY);
//    cv::cvtColor(toolImage,toolImage,cv::COLOR_BGR2GRAY);
//    cv::cvtColor(inspectImage,inspectImage,cv::COLOR_BGR2GRAY);
    DEBUG_OUT<<" tmplImage channels "<<tmplImage.channels()<< std::endl;
    DEBUG_OUT<<" toolImage channels "<<toolImage.channels()<< std::endl;
    int w=inspectImage.size().width;
    int h=inspectImage.size().height;
    //602, 294, 341, 379
    //709,709,701,265
    Rect toolRect(709,709,701,265);
//    Rect toolRect(563,291,1075-563,777-291);

    std::vector<Rect> markerList;
    markerList.push_back(Rect(0,0,w/2,h/2));
    markerList.push_back(Rect(w/2,0,w/2,h/2));
    markerList.push_back(Rect(0,h/2,w/2,h/2));
    markerList.push_back(Rect(w/2,h/2,w/2,h/2));
    float resScore;
    int resState;
    //inspect.setDebugInfo(false);
    inspect.setCheckStateParam(15);
    std::vector<Point2f> resRect;

    inspect.setTmplImageAndMarker(tmplImage,markerList);

    inspect.setCurrentInspectImage(inspectImage);

    resState = inspect.inspection(toolRect,resRect,resScore);
    if(resState<ERR_NO_TEMPLATE_)
    {
        DEBUG_OUT<<" point 1:"<<resRect[0].x<<" "<<resRect[0].y<<std::endl;
        DEBUG_OUT<<" point 2:"<<resRect[1].x<<" "<<resRect[1].y<<std::endl;
        DEBUG_OUT<<" point 3:"<<resRect[2].x<<" "<<resRect[2].y<<std::endl;
        DEBUG_OUT<<" point 4:"<<resRect[3].x<<" "<<resRect[3].y<<std::endl;
        DEBUG_OUT<<" Tool State: "<<resState<<" resScore:"<<resScore<<std::endl;
    }
    else
    {
        DEBUG_OUT<<" inspect Img error!"<<std::endl;
    }
    DEBUG_OUT<<" Press 'q' to exit!"<<std::endl;
    while(std::getchar() == 'q');
    return 0;
}

