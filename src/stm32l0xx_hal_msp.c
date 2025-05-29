/**********************************************************************************************************************
 * \file stm32l0xx_hal_msp.c
 *
 * \author  MarcoAAG
 *
 * \date Oct-03-2024
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include "stm32l0xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* Enable USARTx clock */
  __HAL_RCC_USART2_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = GPIO_PIN_2; // A7
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_USART2;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = GPIO_PIN_3; // A2
  GPIO_InitStruct.Alternate = GPIO_AF4_USART2;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  /*##-1- Reset peripherals ##################################################*/
  __HAL_RCC_USART2_FORCE_RESET();
  __HAL_RCC_USART2_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);
}

#ifdef __cplusplus
}
#endif
