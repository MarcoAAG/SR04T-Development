/**********************************************************************************************************************
 * \file template_app.c
 *
 * \author MarcoAAG
 *
 * \date April-18-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <sr04t.h>
#include <stm32l0xx_hal.h>
#include <system_clock.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t SR04T_WriteCommand(uint8_t* pData, uint8_t Length);
static uint32_t SR04T_ReadData(uint8_t* pData, uint8_t Length);

SR04T_IO_t SR04T_IO = {
  .WriteReg = SR04T_WriteCommand,
  .ReadReg  = SR04T_ReadData,
};

SR04T_Object_t     SR04T_Obj;
UART_HandleTypeDef UartHandle;

int main()
{
  HAL_Init();

  // Configure the system clock to 2 MHz
  SYSTEMCLOCK_v_Config();

  /*Configure the UART peripheral */
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
      - Stop Bit    = One Stop bit
      - Parity      = ODD parity
      - BaudRate    = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance = USART2;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
  }

  SR04T_v_INIT(&SR04T_Obj, &SR04T_IO);

  // Infinite loop
  while(1)
  {
    SR04T_u_GetDistance(&SR04T_Obj);
    HAL_Delay(1000);
  }
}

static uint32_t SR04T_WriteCommand(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Transmit(&UartHandle, pData, Length, 5000);
  return 0;
}

static uint32_t SR04T_ReadData(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Receive(&UartHandle, pData, Length, 5000);
  return 0;
}

#ifdef __cplusplus
}
#endif
