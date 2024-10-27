/**
 * main.c
 */

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include "timer.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

#define PERIOD_BALIZA_MS        500U
#define PERIOD_SW_MS            10U


/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void boardInit(void);

static void sw_periodic (void);
static void baliza_periodic (void);


/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static unsigned char tim_baliza;
static int sw_press_event=0;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void App_Init (void)
{
    boardInit();

    Timer_Init();
    Timer_Start(Timer_GetId(), TIMER_MS2TICKS(PERIOD_SW_MS), TIM_MODE_PERIODIC, sw_periodic); // configure periodic SWITCH read
    tim_baliza = Timer_GetId(); // Get baliza's timer
}


void App_Run (void)
{
    static char baliza_state = 0;

    if (sw_press_event)
    { // toggleo estado baliza
        sw_press_event = 0;
        baliza_state = !baliza_state;

        if (baliza_state)
        {
            Timer_Start(tim_baliza, TIMER_MS2TICKS(PERIOD_BALIZA_MS), TIM_MODE_PERIODIC, baliza_periodic); // Start periodic BALIZA blink
            digitalWrite(PIN_LED_RED, LED_ACTIVE);
            digitalWrite(PIN_LED_YELLOW, LED_ACTIVE);
        }
        else
        {
            Timer_Stop(tim_baliza); // Stop BALIZA blink
            digitalWrite(PIN_LED_RED, !LED_ACTIVE);
            digitalWrite(PIN_LED_YELLOW, !LED_ACTIVE);
        }
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void boardInit(void)
{
	pinMode(PIN_LED_RED, OUTPUT); // configure LEDs
	digitalWrite(PIN_LED_RED, !LED_ACTIVE);
	pinMode(PIN_LED_YELLOW, OUTPUT);
	digitalWrite(PIN_LED_YELLOW, !LED_ACTIVE);
	pinMode(PIN_LED_BLUE, OUTPUT);
	digitalWrite(PIN_LED_BLUE, !LED_ACTIVE);

	pinMode(PIN_SW2, SW_INPUT_TYPE); // configure switches
	pinMode(PIN_SW3, SW_INPUT_TYPE);
}


static void sw_periodic (void)
{
    static int sw_old = !SW_ACTIVE;
    int sw_new;

    // Lectura y accion del pulsador
    sw_new = digitalRead(PIN_SW3);
    if ((sw_old == !SW_ACTIVE) && (sw_new == SW_ACTIVE))
    { // Se presionó el pulsador! Evento detectado
        sw_press_event = 1; //
    }
    sw_old = sw_new; // actualizo estado switch para el próximo loop
}


static void baliza_periodic (void)
{
    digitalToggle(PIN_LED_YELLOW);
}


