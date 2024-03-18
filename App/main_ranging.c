/*!
 * \file      main-RangingDemo.c
 *
 * \brief     Main Program body of the Ranging demo.
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


/* Includes ------------------------------------------------------------------*/

#include "boards.h"
#include "sx1280.h"
#include "radio.h"
#include "utilities.h"
#include <stdio.h>
#include "demoRanging.h"
#include "RangingDisplay.h"
#include "SEGGER_RTT.h"


/****************************************************************************\
 * CONSTANT and MACRO definition
\****************************************************************************/

//#define DEMO_SETTING_ENTITY                           SLAVE

#define PROXBUFFERSIZE                                   20


/***************************************************************************\
 * RAM data
\***************************************************************************/

/***************************************************************************\
 * Local function Prototype
\***************************************************************************/

/***************************************************************************\
 * Ranging Demo Main function
\***************************************************************************/
uint8_t ranging_role = MASTER;

int main_ranging(void)
{
	uint16_t FwVersion=0;
    uint8_t  keyVal = 0;

    //读取PA7和PA15的值
    keyVal = 0;
    keyVal |= HAL_GPIO_ReadPin(KEY_SX1280_PORT, KEY_SX1280_PIN);
    keyVal <<= 1;
    keyVal |= HAL_GPIO_ReadPin(KEY_460800_PORT, KEY_460800_PIN);

    if (keyVal == 0x00) {
        ranging_role = MASTER;
        HAL_GPIO_WritePin(LED_G_PORT, LED_G_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_SET  );
    } else {
        ranging_role = SLAVE;
        HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_G_PORT, LED_G_PIN, GPIO_PIN_SET  );
    }

    /* 1- Initialize the Ranging Application */
    RangingDemoInitApplication(ranging_role /* DEMO_SETTING_ENTITY */);

    RangingDemoSetRangingParameters( 40u, DEMO_RNG_ADDR_1, DEMO_RNG_ANT_1, DEMO_RNG_UNIT_SEL_M );
    RangingDemoSetRadioParameters( LORA_SF6, LORA_BW_1600, LORA_CR_4_5, DEMO_CENTRAL_FREQ_PRESET2, DEMO_POWER_TX_MAX );
	
	Radio.Reset();
	FwVersion = Radio.GetFirmwareVersion();

	printf("\n");
	if(ranging_role /* DEMO_SETTING_ENTITY */ == MASTER)
	{
		printf("Ranging Demo as Master\n");
	}
	else
	{
		printf("Ranging Demo as Slave\n");
	}

    printf("Init finish, firmware 0x%x!\n", FwVersion);
    
    /* Infinite loop */
    while(1){
        
        RangingDemoStatus_t demoStatus;
        // Run the ranging demo.
        do{
            demoStatus = RangingDemoRun();
        }while( demoStatus == DEMO_RANGING_RUNNING);

        // If master, display the ranging result.
        if( ranging_role /* DEMO_SETTING_ENTITY */ == MASTER){
            //ggg RangingDisplayUartOutputData( );
            RangingDisplayUartOutputDistance( );
        }

        if( demoStatus != DEMO_RANGING_TERMINATED ){
            RangingDemoReset();
        }
    }
}

/***************************************************************************\
 * Local Function Definition
\***************************************************************************/


