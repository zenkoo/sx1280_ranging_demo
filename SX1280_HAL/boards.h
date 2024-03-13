#ifndef __BOARDS_H__
#define __BOARDS_H__
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "utilities.h"
#include "hw-spi.h"
#include "hw-gpio.h"
#include "hw-lptim.h"

extern void Error_Handler(void);

// STM32F103C8T6
#define RADIO_NSS_PIN        GPIO_PIN_12
#define RADIO_NSS_PORT       GPIOA
#define RADIO_MOSI_PIN       GPIO_PIN_7
#define RADIO_MOSI_PORT      GPIOA
#define RADIO_MISO_PIN       GPIO_PIN_6
#define RADIO_MISO_PORT      GPIOA
#define RADIO_SCK_PIN        GPIO_PIN_5
#define RADIO_SCK_PORT       GPIOA
#define RADIO_nRESET_PIN     GPIO_PIN_3
#define RADIO_nRESET_PORT    GPIOB
#define RADIO_BUSY_PIN       GPIO_PIN_8
#define RADIO_BUSY_PORT      GPIOA
#define RADIO_DIO1_Pin 		 GPIO_PIN_15
#define RADIO_DIO1_GPIO_Port GPIOB
#define RADIO_DIO2_Pin 		 GPIO_PIN_15
#define RADIO_DIO2_GPIO_Port GPIOB
#define RADIO_DIO3_Pin 		 GPIO_PIN_15
#define RADIO_DIO3_GPIO_Port GPIOB
#define RADIO_DIOx_PIN       GPIO_PIN_15
#define RADIO_DIOx_PORT      GPIOB

#define USART_TX_PIN        GPIO_PIN_10
#define USART_TX_PORT       GPIOB
#define USART_RX_PIN        GPIO_PIN_11
#define USART_RX_PORT       GPIOB
#define ANT_SW_PIN          GPIO_PIN_14
#define ANT_SW_PORT         GPIOC
#define LED_RX_PIN          GPIO_PIN_14
#define LED_RX_PORT         GPIOC
#define LED_TX_PIN          GPIO_PIN_15
#define LED_TX_PORT         GPIOC

#endif