/**********************************************************************************************************************
 * \file sr04t.c
 *
 * \author MarcoAAG
 *
 * \date May-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef SR04T_H
#define SR04T_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define SR04T_OK    (0)
#define SR04T_ERROR (1)

typedef uint32_t (*SR04T_WriteReg_Func)(uint8_t*, uint8_t);
typedef uint32_t (*SR04T_ReadReg_Func)(uint8_t*, uint8_t);
typedef uint32_t (*SR04T_Write_Func)(void*, uint8_t*, uint8_t); /*  this will connect to the LCD_IO_WriteData */
typedef uint32_t (*SR04T_Read_Func)(void*, uint8_t*, uint8_t);  /*  this will connect to the LCD_IO_ReadData */

typedef struct
{
  SR04T_Write_Func WriteReg;
  SR04T_Read_Func  ReadReg;
  void*            handle;
} SR04T_ctx_t;

typedef struct
{
  SR04T_WriteReg_Func WriteReg;
  SR04T_ReadReg_Func  ReadReg;
} SR04T_IO_t;

typedef struct
{
  SR04T_IO_t  IO;
  SR04T_ctx_t Ctx;
  uint8_t     IsInitialized;
} SR04T_Object_t;

uint8_t  SR04T_v_INIT(SR04T_Object_t* pObj, SR04T_IO_t* pIO);
uint16_t SR04T_u_GetDistance(SR04T_Object_t* pObj);

#ifdef __cplusplus
}
#endif

#endif // SR04T_H