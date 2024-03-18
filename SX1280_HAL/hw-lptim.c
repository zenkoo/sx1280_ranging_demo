/*!
 * \file      hw-lptim.c
 *
 * \brief     Timer driver implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Semtech
 */

/* Includes -----------------------------------------------------------------*/

#include "boards.h"

/****************************************************************************\
 *  Type definition
\****************************************************************************/

/**
 * TimerFunc type
 *
 *     Type for a timer notification callback. The notification function
 *     is called to indicate that the timer has fired.
 */
typedef void (*TimerFunc)(void *parms);

/* Function callback to call when timer has fired */
static TimerFunc timerFunction;
static void *timerParam;

static bool     timerSetFlag = false;
static uint32_t timerStart = 0;
static uint32_t timerWait = 0;

/*!
 * \brief Creates an autoreload timer.
 *
 * \param [in] func         A pointer to a function to call when the timer
 *                          expires.
 * \param [in] param        Parameter to pass in func when the timer expires.
 * \param [in] millisec     Time to wait before the timer expiration.
 *
 */
void TimerCreateTimer(void *func, void *param, uint32_t millisec){
    timerSetFlag = true;
    timerStart = HAL_GetTick();
    timerWait  = millisec;
    //printf("TimerCreateTimer: %d\n", millisec);
    timerFunction = (TimerFunc)func;
    timerParam    = param;
}

/*!
 * \brief Cancel the current running timer.
 *
 */
void TimerCancelTimer(void){
    timerSetFlag = false;
    timerStart = 0;
    timerWait  = 0;
    //printf("TimerCancelTimer\n");
    timerFunction = NULL;
    timerParam    = NULL;
}

void TimerSysTick_IRQHandler(void){
    if (timerSetFlag == true){
        if (HAL_GetTick() - timerStart >= timerWait){
            if (timerFunction) {
                //printf("TimerSysTick_IRQHandler: %d\n", timerWait);
                timerFunction(timerParam);
            }
            timerSetFlag = false;
            timerStart = 0;
            timerWait  = 0;
        }
    }
}


