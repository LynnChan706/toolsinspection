#include "checktoolstate.h"
#include <iostream>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algcommon.h"

CheckToolState::CheckToolState()
{
    _detector=new SurfFeatureDetector(FEATURE_VALUE);
}

float CheckToolState::getToolState(Mat tmplImg, Mat inspectImg)
{
    if(tmplImg.empty() ||inspectImg.empty() ||tmplImg.channels() != inspectImg.channels() )
    {
        DEBUG_STATE_OUT<<" error image empty! "<<std::endl;
        return -1;
    }
    Mat procesImg;
    adaptiveBrightness(tmplImg, inspectImg, procesImg);
    std::vector<cv::KeyPoint> keypoints1;
    std::vector<cv::KeyPoint> keypoints2;
    _detector->detect(tmplImg,keypoints1);
    _detector->detect(procesImg,keypoints2);


    DEBUG_STATE_OUT << " Number of SURF points (template): "  << keypoints1.size() << std::endl;
    DEBUG_STATE_OUT << " Number of SURF points (inspect): "  << keypoints2.size() << std::endl;

    int kp1= keypoints1.size() <10?10: keypoints1.size() ;
    int kp2= keypoints2.size();
    float score= kp2>=kp1?1.0:float(kp2)/float(kp1);

    DEBUG_STATE_OUT << " State key size score : "  <<score << std::endl;

    Mat result;
    matchTemplate(procesImg, tmplImg, result, TM_CCOEFF_NORMED);

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    DEBUG_STATE_OUT << " Max matchTemplate value : "  <<maxVal << std::endl;
    maxVal=maxVal>0?maxVal:0;
    score=score*maxVal*100;
    DEBUG_STATE_OUT << " Check state out score:  "  <<score << std::endl;
    return score;

    //    Mat diffInspectImg;
    //    absdiff(tmplImg,inspectImg,diffInspectImg);
    //    Scalar inspectMean;
    //    Scalar inspectStddev;
    //    meanStdDev(diffInspectImg,inspectMean,inspectStddev);
    //    float inspectRes=-1;
    //    if(tmplImg.channels() ==3)
    //    {
    //        DEBUG_STATE_OUT<<"  Inspect Mean: "<<inspectMean.val[0]<<"  "<<inspectMean.val[1]<<"  "<<inspectMean.val[2]<<std::endl;
    //        DEBUG_STATE_OUT<<"  Inspect Stddev: "<<inspectStddev.val[0]<<"  "<<inspectStddev.val[1]<<"  "<<inspectStddev.val[2]<<std::endl;
    //        inspectRes=(inspectStddev.val[0]+inspectStddev.val[1]+inspectStddev.val[2])/3;
    //    }
    //    else
    //    {
    //        DEBUG_STATE_OUT<<"  Inspect Mean: "<<inspectMean.val[0]<<std::endl;
    //        DEBUG_STATE_OUT<<"  Inspect Stddev: "<<inspectStddev.val[0]<<std::endl;
    //        inspectRes=inspectStddev.val[0];
    //    }
    //    DEBUG_STATE_OUT<<" Tool inspectRes: "<<inspectRes<<std::endl;
    //    cv::imshow("res",diffInspectImg);
    //    cv::waitKey(IMG_SHOW_TIME);
    //    cv::destroyAllWindows();
    //    return inspectRes;
}
bool CheckToolState::adaptiveBrightness(Mat tmplImg, Mat inspectImg, Mat &resImg)
{
    Mat orghsv,temphsv,resTempimg;
    Scalar inspectMean,tempMean;
    Scalar inspectStddev,tempStddev;

    cvtColor(tmplImg,temphsv,COLOR_BGR2HSV);
    cvtColor(inspectImg,orghsv,COLOR_BGR2HSV);

    meanStdDev(orghsv,inspectMean,inspectStddev);
    meanStdDev(temphsv,tempMean,tempStddev);
    float f=1;
    if(inspectMean[2]>0)
    {
        f=tempMean.val[2]/inspectMean[2];
    }
    DEBUG_STATE_OUT << " Brightness F value : "  <<f << std::endl;
    if(f>1)
    {
        for(int i=0;i<orghsv.rows;i++)
        {
            for(int j=0;j<orghsv.cols;j++)
            {
                if(orghsv.at<Vec3b>(i,j)[2]*f<255)
                {
                    orghsv.at<Vec3b>(i,j)[2] *=f;
                }
                else
                {
                    orghsv.at<Vec3b>(i,j)[2]=255;
                }
            }
        }
    }
    cvtColor(orghsv,resTempimg,COLOR_HSV2BGR);
    resTempimg.copyTo(resImg);

//    cv::imshow("testimg",resTempimg);
//    cv::waitKey(0);
//    cv::destroyAllWindows();
    return true;
}

