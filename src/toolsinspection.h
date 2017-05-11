#ifndef TOOLSINSPECTION_H
#define TOOLSINSPECTION_H

#include "toolsinspection_global.h"
#include "opencv2/core/core.hpp"

using namespace cv;

class TOOLSINSPECTIONLIBSHARED_EXPORT ToolsInspection
{
public:
	ToolsInspection();
	~ToolsInspection();
    int inspection(Mat inspectImage,Mat tmplImage,Mat toolImage,Rect toolrect);
};

#endif //TOOLSINSPECTION_H

