#include "toolsinspection.h"
#include "opencv2/core/core.hpp"
using namespace cv;
int main(int argc, char *argv[])
{
    ToolsInspection inspect;
    Mat inspectImage;
    Mat tmplImage;
    Mat toolImage;
    Rect toolRect;
    Rect resRect;
    inspect.inspection(inspectImage,tmplImage,toolRect,resRect);
    return 0;
}

