#ifndef ALGCOMMON_HPP
#define ALGCOMMON_HPP

#include <iostream>

#ifdef LOG_INFO
#define FUN_INFO(...) std::cout<<"[ALG INFO]: "<<__FUNCTION__<<" "<< __LINE__<<" "<<##__VA_ARGS__<<std::endl
#define DEBUG_OUT std::cout<<"[ALG INFO]: "<<__FUNCTION__<<" "<< __LINE__<<" "<<

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

#define LOG_DEBUG "DEBUG"
#define LOG_TRACE "TRACE"
#define LOG_ERROR "ERROR"
#define LOG_INFOR "INFOR"
#define LOG_CRTCL "CRTCL"

#define LOG_OUT(level, format, ...)
#endif
/*
struct _Rect
{
public:
    int x=0;
    int y=0;
    int width=0;
    int height=0;
};

struct _RectF
{
public:
    int x=0;
    int y=0;
    int width=0;
    int height=0;
};
*/
#endif // ALGCOMMON_HPP
