#ifndef CHESSMARKER_H
#define CHESSMARKER_H

#include <vector>
#include <opencv2/core/core.hpp>

using namespace cv;

class ChessMarker
{
public:

    ChessMarker();

    bool getTransform(const Mat tempImg, const Mat inspectImg,
                         std::vector<Rect> markerList,
                      Mat &warpMat);

    bool getMakerPointList(const Mat makerImage, Size makerSize,
                           Point2f & pos);

};

#endif // CHESSMARKER_H
