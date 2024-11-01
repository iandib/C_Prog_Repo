/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   Nicolás Magliola
 ******************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/***** BOARD defines **********************************************************/

// On Board User LEDs
#define PIN_LED_RED     PORTNUM2PIN(PB,22) // PTB22
#define PIN_LED_GREEN   PORTNUM2PIN(PE,26) // PTE26
#define PIN_LED_BLUE    PORTNUM2PIN(PB,21) // PTB21

#define LED_ACTIVE      LOW


// On Board User Switches
#define PIN_SW2         PORTNUM2PIN(PC,6) // PTC6
#define PIN_SW3         PORTNUM2PIN(PA,4) // PTA4

#define SW_ACTIVE       LOW
#define SW_INPUT_TYPE   INPUT_PULLUP


// PWM Pinout

#define PIN_PWM_H1      PORTNUM2PIN(PD,0)
#define PIN_PWM_L1      PORTNUM2PIN(PD,1)
#define PIN_PWM_H2      PORTNUM2PIN(PD,2)
#define PIN_PWM_L2		PORTNUM2PIN(PD,3)

#define PWM_ACTIVE		HIGH



/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
