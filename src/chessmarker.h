#ifndef CHESSMARKER_H
#define CHESSMARKER_H

#include <vector>
#include <opencv2/core/core.hpp>

using namespace cv;

class ChessMarker
{
public:

    ChessMarker();
    int getMakerPointList(const Mat makerImage, Size &makerSize);

};

#endif // CHESSMARKER_H
