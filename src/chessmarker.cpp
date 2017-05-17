#include "chessmarker.h"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"

ChessMarker::ChessMarker()
{

}

int ChessMarker::getMakerPointList(const Mat makerImage,cv::Size &makerSize)
{
    // the points on the makerImage
    std::vector<cv::Point2f> imageCorners;
    // Get corners
    Mat makerShow;
    cv::cvtColor(makerImage,makerShow,cv::COLOR_BGR2GRAY);

    bool found = cv::findChessboardCorners(
                            makerShow, makerSize, imageCorners);
//    cv::cornerSubPix(makerShow, imageCorners,
//              cv::Size(5,5),
//              cv::Size(-1,-1),
//        cv::TermCriteria(cv::TermCriteria::MAX_ITER +
//                      cv::TermCriteria::EPS,
//         30,
//         0.1));


//    makerImage.copyTo(makerShow);
    //Draw the corners

    std::cout<<"maker foound"<<found<<std::endl;
    for(int i =0;i<imageCorners.size();i++)
    {
        std::cout<<imageCorners.at(i).x
                <<" "<<imageCorners.at(i).y<<std::endl;
    }

    cv::drawChessboardCorners(makerShow, makerSize, imageCorners, found);
    cv::resize(makerShow,makerShow,
               cv::Size(makerShow.size().width/4,makerShow.size().height/4));
    cv::imshow("Corners on makerImage", makerShow);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
