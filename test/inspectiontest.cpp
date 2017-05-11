#include "toolsinspection.h"

using namespace cv;
int main(int argc, char *argv[])
{
    ToolsInspection inspect;
    Mat inspectImage;
    Mat tmplImage;
    Mat toolImage;
    Rect toolRect;
    inspect.inspection(inspectImage,tmplImage,toolImage,toolRect);
    return 0;
}

