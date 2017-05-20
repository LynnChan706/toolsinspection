#include "checktoolstate.h"
#include <iostream>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "algcommon.h"

CheckToolState::CheckToolState()
{

}

float CheckToolState::getToolState(Mat tmplImg, Mat inspectImg)
{
    if(tmplImg.empty() ||inspectImg.empty() ||tmplImg.channels() != inspectImg.channels() )
    {
        DEBUG_STATE_OUT<<" error image empty! "<<std::endl;
        return -1;
    }

    Mat diffInspectImg;
    absdiff(tmplImg,inspectImg,diffInspectImg);
    Scalar inspectMean;
    Scalar inspectStddev;
    meanStdDev(diffInspectImg,inspectMean,inspectStddev);
    float inspectRes=-1;
    if(tmplImg.channels() ==3)
    {
        DEBUG_STATE_OUT<<"  Inspect Mean: "<<inspectMean.val[0]<<"  "<<inspectMean.val[1]<<"  "<<inspectMean.val[2]<<std::endl;
        DEBUG_STATE_OUT<<"  Inspect Stddev: "<<inspectStddev.val[0]<<"  "<<inspectStddev.val[1]<<"  "<<inspectStddev.val[2]<<std::endl;
        inspectRes=(inspectStddev.val[0]+inspectStddev.val[1]+inspectStddev.val[2])/3;
    }
    else
    {
        DEBUG_STATE_OUT<<"  Inspect Mean: "<<inspectMean.val[0]<<std::endl;
        DEBUG_STATE_OUT<<"  Inspect Stddev: "<<inspectStddev.val[0]<<std::endl;
        inspectRes=inspectStddev.val[0];
    }
    DEBUG_STATE_OUT<<" Tool inspectRes: "<<inspectRes<<std::endl;
//    cv::imshow("res",diffInspectImg);
//    cv::waitKey(IMG_SHOW_TIME);
//    cv::destroyAllWindows();
    return inspectRes;
}
