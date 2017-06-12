#ifndef ALGCOMMON_H
#define ALGCOMMON_H

#include <iostream>

#ifdef LOG_INFO
#define FUN_INFO(...) std::cout<<"[ALG INFO]: "<<__FUNCTION__<<" "<< __LINE__<<" "<<##__VA_ARGS__<<std::endl
#define DEBUG_OUT  std::cout<<"[ALG INFO]: "<<__FUNCTION__<<" "<< __LINE__

#define LOG_DEBUG "DEBUG"
#define LOG_TRACE "TRACE"
#define LOG_ERROR "ERROR"
#define LOG_INFOR "INFOR"
#define LOG_CRTCL "CRTCL"

#define LOG_OUT(level, format, ...) \
    do { \
        std::fprintf(stderr, "[%s|%s@%s,%d] " format "\n", \
            level, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__ ); \
    } while (0)

#else

#define FUN_INFO(...)
#define DEBUG_OUT std::cout<<"[ALG INFO]: "<<__FUNCTION__<<" "<< __LINE__<<" "

#define LOG_DEBUG "DEBUG"
#define LOG_TRACE "TRACE"
#define LOG_ERROR "ERROR"
#define LOG_INFOR "INFOR"
#define LOG_CRTCL "CRTCL"

#define LOG_OUT(level, format, ...)
#endif

#define CHESS_W 3
#define CHESS_H 3
#define MARKER_MINSIZE 4
#define DIFF_TMPL_VALUE 5

enum INSPECTRES
{
    TOOL_EXIST = 1,
    TOOL_INEXIST = 2,
    TOOL_UNKNOWN = 3,
    ERR_NO_TEMPLATE = 4,
    ERR_INSPECT_IMG = 5
};

#define ContainsRect( m, roi) (0 <= roi.x && 0 <= roi.width && \
                               roi.x + roi.width <= m.cols && \
                               0 <= roi.y && 0 <= roi.height && \
                               roi.y + roi.height <= m.rows)
struct DebugState
{
    static bool _bDebugState;
};

#define IMG_SHOW_TIME 500
#define MIN_FEATURE_NUM 30
#define DEBUG_STATE if(DebugState::_bDebugState)
#define DEBUG_STATE_OUT DEBUG_STATE DEBUG_OUT

#endif // ALGCOMMON_H
