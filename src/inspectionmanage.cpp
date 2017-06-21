#include "inspectionmanage.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/features2d/features2d.hpp>
#include "algcommon.h"
#include "chessmarker.h"
#include "checktoolstate.h"


InspectionManage::InspectionManage()
{
    _pChessMaker = new ChessMarker();
    _pCheckState = new CheckToolState();
    _stateThreshold = 14;

}

InspectionManage::~InspectionManage()
{
    if(_pChessMaker != NULL)
    {
        delete _pChessMaker;
        _pChessMaker = NULL;
    }
    if(_pCheckState != NULL)
    {
        delete _pCheckState;
        _pCheckState = NULL;
    }
}

bool InspectionManage::setTmplImageAndMarker(Mat tmplImage,
                                             std::vector<Rect> markerList)
{
    if(tmplImage.empty())
    {
        return false;
    }
    else
    {
        tmplImage.copyTo(_tmplImage);
        if(_tmplImage.channels()==1)
        {
            cv::cvtColor(_tmplImage,_tmplImage,cv::COLOR_GRAY2BGR);
        }
        _markerList = markerList;
        return true;
    }
}

void InspectionManage::setDebugInfo(bool debugState)
{
    DebugState::_bDebugState = debugState;
}

void InspectionManage::setCheckStateParam(float thresholdValue)
{
    _stateThreshold=thresholdValue;
}

bool InspectionManage::setCurrentInspectImage(Mat inspectImage)
{
    inspectImage.copyTo(_inspectImage);
    if(!_loctImage.empty())
    {
        _loctImage.release();
    }
    if (_tmplImage.empty() || _inspectImage.empty() )
    {
        DEBUG_STATE_OUT<<" template or inspect image empty!"<<std::endl;
        return false;
    }
    if(_inspectImage.channels()==1)
    {
        cv::cvtColor(_inspectImage,_inspectImage,cv::COLOR_GRAY2BGR);
    }
    bool locState = false;

    DEBUG_STATE_OUT<<" SIFT Location! "<<std::endl;
    Matcher rmatcher;
    rmatcher.setConfidenceLevel(0.99);
    rmatcher.setMinDistanceToEpipolar(1.0);
    rmatcher.setRatio(3.95f);
    cv::Ptr<cv::FeatureDetector> pfd = new SurfFeatureDetector(2000);
    rmatcher.setFeatureDetector(pfd);
    // Match the two images
    std::vector<cv::DMatch> matches;
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    Mat processimg;
    _pCheckState->adaptiveBrightness(_tmplImage,_inspectImage,processimg);
    bool checkres=false;
    rmatcher.match(_tmplImage,processimg,matches, keypoints1, keypoints2,checkres);
    if(checkres)
    {
        locState =getHomography(matches,keypoints1,keypoints2);
    }

    if (!locState && _markerList.size()!= 0 )
    {
        locState = _pChessMaker->getTransform(
                    _tmplImage,_inspectImage,
                    _markerList,_warpMat);
        if(locState)
        {
            DEBUG_STATE_OUT<<" Chessmarker Location success!"<<std::endl;
        }
        else
        {
            DEBUG_STATE_OUT<<" Chessmarker Location error!"<<std::endl;
        }
    }

    if(locState && (!_warpMat.empty()) )
    {
        std::vector<Point2f> obj_corners(4);
        obj_corners[0]=Point2f(0,0);
        obj_corners[1]=Point2f(_tmplImage.size().width, 0);
        obj_corners[2]=Point2f(0, _tmplImage.size().height);
        obj_corners[3]=Point2f(_tmplImage.size().width,_tmplImage.size().height);

        DEBUG_STATE_OUT<<" point 1:"<<obj_corners[0].x<<" "<<obj_corners[0].y<<std::endl;
        DEBUG_STATE_OUT<<" point 2:"<<obj_corners[1].x<<" "<<obj_corners[1].y<<std::endl;
        DEBUG_STATE_OUT<<" point 3:"<<obj_corners[2].x<<" "<<obj_corners[2].y<<std::endl;
        DEBUG_STATE_OUT<<" point 4:"<<obj_corners[3].x<<" "<<obj_corners[3].y<<std::endl;

        std::vector<Point2f> resRect(4);
        perspectiveTransform(obj_corners, resRect, _warpMat);

        DEBUG_STATE_OUT<<" point 1:"<<resRect[0].x<<" "<<resRect[0].y<<std::endl;
        DEBUG_STATE_OUT<<" point 2:"<<resRect[1].x<<" "<<resRect[1].y<<std::endl;
        DEBUG_STATE_OUT<<" point 3:"<<resRect[2].x<<" "<<resRect[2].y<<std::endl;
        DEBUG_STATE_OUT<<" point 4:"<<resRect[3].x<<" "<<resRect[3].y<<std::endl;
        warpPerspective(_inspectImage,_loctImage,_warpMat,_tmplImage.size());
        DEBUG_STATE
        {
            Mat locimg;
            cv::resize(_loctImage,locimg,cv::Size(_loctImage.size().width/4,_loctImage.size().height/4));
            cv::imshow("locimg",locimg);
            cv::waitKey(IMG_SHOW_TIME);
            cv::destroyAllWindows();
        }
    }
    return locState;
}

int InspectionManage::inspection(Rect toolRect, std::vector<Point2f> &resRect, float &resScore, Mat toolImage)
{
    if (_loctImage.empty())
    {
        DEBUG_STATE_OUT<<" Inspect image empty!"<<std::endl;
        return ERR_INSPECT_IMG;
    }

    if(ContainsRect(_tmplImage,toolRect))
    {
        std::vector<Point2f> obj_corners(4);
        obj_corners[0]=Point2f(toolRect.x,toolRect.y);
        obj_corners[1]=Point2f(toolRect.x+toolRect.width, toolRect.y);
        obj_corners[2]=Point2f(toolRect.x+toolRect.width, toolRect.y+toolRect.height);
        obj_corners[3]=Point2f(toolRect.x,toolRect.y+toolRect.height);

        DEBUG_STATE_OUT<<" Tmpl point 1:"<<obj_corners[0].x<<" "<<obj_corners[0].y<<std::endl;
        DEBUG_STATE_OUT<<" Tmpl point 2:"<<obj_corners[1].x<<" "<<obj_corners[1].y<<std::endl;
        DEBUG_STATE_OUT<<" Tmpl point 3:"<<obj_corners[2].x<<" "<<obj_corners[2].y<<std::endl;
        DEBUG_STATE_OUT<<" Tmpl point 4:"<<obj_corners[3].x<<" "<<obj_corners[3].y<<std::endl;
        perspectiveTransform(obj_corners, resRect, _warpMat);
        DEBUG_STATE_OUT<<" Roi point 1:"<<resRect[0].x<<" "<<resRect[0].y<<std::endl;
        DEBUG_STATE_OUT<<" Roi point 2:"<<resRect[1].x<<" "<<resRect[1].y<<std::endl;
        DEBUG_STATE_OUT<<" Roi point 3:"<<resRect[2].x<<" "<<resRect[2].y<<std::endl;
        DEBUG_STATE_OUT<<" Roi point 4:"<<resRect[3].x<<" "<<resRect[3].y<<std::endl;
        Mat toolInsImg;
        Mat tmpltoolImg;
        _loctImage(toolRect).copyTo(toolInsImg);
        _tmplImage(toolRect).copyTo(tmpltoolImg);
        DEBUG_STATE
        {
            cv::imshow("tool result",toolInsImg);
            cv::waitKey(IMG_SHOW_TIME);
            cv::destroyAllWindows();
        }
        resScore = _pCheckState->getToolState(tmpltoolImg,toolInsImg);

        float toolsRes;

        if(!toolImage.empty())
        {
            cv::Mat toolbutimg(toolImage);
            if(toolbutimg.channels()==1)
            {
                cv::cvtColor(toolbutimg,toolbutimg,cv::COLOR_GRAY2BGR);
            }

            toolsRes= _pCheckState->getToolState(tmpltoolImg,toolbutimg);
            if(resScore<toolsRes)
            {
                return TOOL_INEXIST;
            }
            else
            {
                return TOOL_EXIST;
            }
        }
        else
        {
            if(resScore<_stateThreshold)
            {
                return TOOL_INEXIST;
            }
            else
            {
                return TOOL_EXIST;
            }
        }
    }
    else
    {
        DEBUG_STATE_OUT<<"ToolRect Error!"<<std::endl;
        return ERR_INSPECT_IMG;
    }
}

bool InspectionManage::getHomography(std::vector<DMatch> &matches,
                                     std::vector<KeyPoint> &keypoints1,
                                     std::vector<KeyPoint> &keypoints2)
{
    std::vector<cv::Point2f> points1, points2;

    for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
         it!= matches.end(); ++it)
    {

        float x= keypoints1[it->queryIdx].pt.x;
        float y= keypoints1[it->queryIdx].pt.y;
        points1.push_back(cv::Point2f(x,y));

        x= keypoints2[it->trainIdx].pt.x;
        y= keypoints2[it->trainIdx].pt.y;
        points2.push_back(cv::Point2f(x,y));

    }
    if(points1.size()<MIN_FEATURE_NUM || points2.size()<MIN_FEATURE_NUM)
    {
        DEBUG_STATE_OUT<<" Location error!"<<std::endl;
        return false;
    }
    std::vector<uchar> inliers(points2.size(),0);
    _warpMat= cv::findHomography(
                cv::Mat(points2),cv::Mat(points1),
                inliers,CV_RANSAC,1.0);
    return true;
}

