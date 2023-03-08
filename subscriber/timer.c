
#include "timer.h"

char* getCurrentTime ()
{
        struct timeval tv;
        int mili;
        const int size = 32;
        char buffer [size];
        char* currentTime = malloc(size);

        gettimeofday(&tv, NULL);
        mili = tv.tv_usec / 1000;

        strftime(buffer, size, "%H:%M:%S", localtime(&tv.tv_sec));

        sprintf(currentTime, "%s:%03d", buffer, mili);

        return currentTime;
}

char* getCurrentTimeWithDate ()
{
        struct timeval tv;
        int mili;
        const int size = 32;
        char buffer [size];
        char* currentTime = malloc(size);

        gettimeofday(&tv, NULL);
        mili = tv.tv_usec / 1000;

        strftime(buffer, size, "%D %H:%M:%S", localtime(&tv.tv_sec));

        sprintf(currentTime, "%s:%03d", buffer, mili);

        return currentTime;
}

uint32_t getTimeStamp()
{
        struct timeval  tv;
        gettimeofday(&tv, NULL);
        
        return (((uint32_t) (tv.tv_usec) + (uint32_t) (tv.tv_sec) * 1000000));
}