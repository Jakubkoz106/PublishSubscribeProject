
#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

/**
 * @brief Get current time.
 * 
 * @return char* current time
 */
char* getCurrentTime ();

/**
 * @brief Get current time with date.
 * 
 * @return char* current time with date
 */
char* getCurrentTimeWithDate ();

/**
 * @brief Get time stamp.
 * 
 * @return uint32_t time stamp
 */
uint32_t getTimeStamp();

#endif