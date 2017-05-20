#include "chessmarker.h"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algcommon.h"

ChessMarker::ChessMarker()
{

}

bool ChessMarker::getTransform(const Mat tempImg, const Mat inspectImg,
                                  std::vector<Rect> markerList, Mat &warpMat)
{
    if(markerList.size() < MARKER_MINSIZE)
    {
        return false;
    }
    std::vector<Point2f> tmplPosList;
    std::vector<Point2f> insPosList;
    for(int i=0; i<markerList.size(); i++)
    {
        Rect roi = markerList.at(i);
        Mat tmplRoiImg;
        Mat insRoiImg;
        Size mSize(CHESS_W,CHESS_H);
        Point2f tPos;
        Point2f iPos;
        try
        {
            if(ContainsRect(tempImg,roi)&&ContainsRect(tempImg,roi))
            {
                tempImg(roi).copyTo(tmplRoiImg);
                inspectImg(roi).copyTo(insRoiImg);
                if(getMakerPointList(tmplRoiImg,mSize,tPos)&&
                        getMakerPointList(insRoiImg,mSize,iPos))
                {
                    tPos.x += roi.x;
                    tPos.y += roi.y;
                    iPos.x += roi.x;
                    iPos.y += roi.y;
                    DEBUG_STATE_OUT<<" marker pos tmpl:"<<tPos.x<<" "<<tPos.y<<std::endl;
                    DEBUG_STATE_OUT<<" marker pos pro:"<<iPos.x<<" "<<iPos.y<<std::endl;

                    tmplPosList.push_back(tPos);
                    insPosList.push_back(iPos);
                    DEBUG_STATE_OUT<<std::endl;
                }
            }
            DEBUG_STATE_OUT<<" tmpl marker size:"<<tmplPosList.size()<<std::endl;
            DEBUG_STATE_OUT<<" ins marker size:"<<insPosList.size()<<std::endl;
        }
        catch(...)
        {
            DEBUG_STATE_OUT<<"Get chess marker error! May be the ROI area error!"<<std::endl;
            return false;
        }
    }
    if (tmplPosList.size() < MARKER_MINSIZE)
    {
        return false;
    }
    //For future use.
    Point2f srcTri[MARKER_MINSIZE];
    Point2f dstTri[MARKER_MINSIZE];
    for(int i=0; i<MARKER_MINSIZE; i++)
    {
        srcTri[i]=insPosList[i];
        dstTri[i]=tmplPosList[i];
    }
    warpMat=getPerspectiveTransform(srcTri,dstTri);
//    Mat res;
//    warpPerspective(inspectImg,res,warpMat,tempImg.size());
//    cv::resize(res,res,
//               cv::Size(tempImg.size().width/4,
//               tempImg.size().height/4));
//    cv::imshow("chessmarker result",res);
//    cv::waitKey(IMG_SHOW_TIME);
//    cv::destroyAllWindows();
    return true;
}


bool ChessMarker::getMakerPointList(const Mat makerImage, Size makerSize, Point2f &pos)
{

    std::vector<cv::Point2f> imageCorners;

    Mat makerShow;
    if (makerImage.channels() == 3)
    {
        cv::cvtColor(makerImage,makerShow,cv::COLOR_BGR2GRAY);
    }
    bool found = cv::findChessboardCorners(
                            makerShow, makerSize, imageCorners);

    DEBUG_STATE_OUT<<" "<<found<<" "<<imageCorners.size()<<std::endl;
//    cv::cornerSubPix(makerShow, imageCorners,
//              cv::Size(5,5),
//              cv::Size(-1,-1),
//        cv::TermCriteria(cv::TermCriteria::MAX_ITER +
//                      cv::TermCriteria::EPS,
//         30,
//         0.1));

    if(found == false || imageCorners.size() != makerSize.width*makerSize.height
            || imageCorners.size() == 0)
    {
        return false;
    }
    cv::Point2f totalpos(0,0);

    for(int i =0;i<imageCorners.size();i++)
    {
        totalpos.x += imageCorners.at(i).x;
        totalpos.y += imageCorners.at(i).y;

    }
    pos.x=totalpos.x/imageCorners.size();
    pos.y=totalpos.y/imageCorners.size();

//    cv::drawChessboardCorners(makerShow, makerSize, imageCorners, found);
//    cv::resize(makerShow,makerShow,
//               cv::Size(makerShow.size().width/4,makerShow.size().height/4));
//    cv::imshow("Corners on makerImage", makerShow);
//    cv::waitKey(IMG_SHOW_TIME);
//    cv::destroyAllWindows();

    return true;
}


