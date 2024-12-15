/***************************************************************************//**
  @file     timer.h
  @brief    Timer driver. Advance implementation
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define TIMER_TICK_MS       1
#define TIMER_MS2TICKS(ms)  ((ms)/TIMER_TICK_MS)

#define TIMERS_MAX_CANT     16
#define TIMER_INVALID_ID    255

#ifndef NULL
#define NULL                ((void*)0)
#endif


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

// Timer Modes
enum { TIM_MODE_SINGLESHOT, TIM_MODE_PERIODIC, CANT_TIM_MODES };


/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Initialice timer and corresponding peripheral
 */
void timerInit(void);


// Non-Blocking services ////////////////////////////////////////////////

/**
 * @brief Request an timer
 * @return ID of the timer to use
 */
char timerGetId(void);


/**
 * @brief Begin to run a new timer
 * @param id ID of the timer to start
 * @param ticks time until timer expires, in ticks
 * @param mode SINGLESHOT or PERIODIC
 * @param callback Function to be call when timer expires
 */
void timerStart(char id, unsigned long ticks, char mode, void (*callback)(void));


/**
 * @brief Finish to run a timer
 * @param id ID of the timer to stop
 */
void timerStop(char id);


/**
 * @brief Verify if a timer has run timeout
 * @param id ID of the timer to check for expiration
 * @return 1 = timer expired
 */
int timerExpired(char id);


// Blocking services ////////////////////////////////////////////////

/**
 * @brief Wait the specified time. Use internal timer
 * @param ticks time to wait in ticks
 */
void timerDelay(unsigned long ticks);


/*******************************************************************************
 ******************************************************************************/

#endif // _TIMER_H_
