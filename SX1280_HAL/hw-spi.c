/*!
 * \file      hw-spi.c
 *
 * \brief     SPI driver implementation
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

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef RadioSpiHandle;
volatile bool blockingDmaFlag;
void SpiInit(void)
{
  //这里将 static void MX_SPI1_Init(void)的内容拷贝到此函数中了

  /* SPI1 parameter configuration*/
  RadioSpiHandle.Instance = SPI1;
  RadioSpiHandle.Init.Mode = SPI_MODE_MASTER;
  RadioSpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
  RadioSpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
  RadioSpiHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
  RadioSpiHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
  RadioSpiHandle.Init.NSS = SPI_NSS_SOFT;
  RadioSpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  RadioSpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
  RadioSpiHandle.Init.TIMode = SPI_TIMODE_DISABLE;
  RadioSpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  RadioSpiHandle.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&RadioSpiHandle) != HAL_OK)
  {
    Error_Handler();
  }
}

void SpiDeInit( void )
{
    HAL_SPI_DeInit( &RadioSpiHandle );
}

#define WAIT_FOR_BLOCKING_FLAG         while( blockingDmaFlag ) { }
/*!
 * @brief Sends txBuffer and receives rxBuffer
 *
 * @param [IN] txBuffer Byte to be sent
 * @param [OUT] rxBuffer Byte to be sent
 * @param [IN] size Byte to be sent
 */
void SpiInOut( uint8_t *txBuffer, uint8_t *rxBuffer, uint16_t size )
{
	#ifdef STM32L4XX_FAMILY
    	HAL_SPIEx_FlushRxFifo( &RadioSpiHandle ); // Comment For STM32L0XX and STM32L1XX Int�gration, uncomment for STM32L4XX Int�gration 
	#endif
    #ifdef USE_DMA
        blockingDmaFlag = true;
        HAL_SPI_TransmitReceive_DMA( &SpiHandle, txBuffer, rxBuffer, size );
        WAIT_FOR_BLOCKING_FLAG
    #else
        HAL_SPI_TransmitReceive( &RadioSpiHandle, txBuffer, rxBuffer, size, HAL_MAX_DELAY );
    #endif
}

void SpiIn( uint8_t *txBuffer, uint16_t size )
{
    #ifdef USE_DMA
        blockingDmaFlag = true;
        HAL_SPI_Transmit_DMA( &SpiHandle, txBuffer, size );
        WAIT_FOR_BLOCKING_FLAG
    #else
        HAL_SPI_Transmit( &RadioSpiHandle, txBuffer, size, HAL_MAX_DELAY );
    #endif
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    blockingDmaFlag = false;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    blockingDmaFlag = false;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
