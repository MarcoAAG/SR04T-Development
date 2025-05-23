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

#include <sr04t.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t SR04T_ReadRegWrap(void* handle, uint8_t* pData, uint8_t Length);
static uint32_t SR04T_WriteRegWrap(void* handle, uint8_t* pData, uint8_t Length);
static uint32_t SR04T_read_reg(SR04T_ctx_t* ctx, uint8_t* data, uint8_t length);
static uint32_t SR04T_write_reg(SR04T_ctx_t* ctx, uint8_t* data, uint8_t length);

uint8_t SR04T_v_INIT(SR04T_Object_t* pObj, SR04T_IO_t* pIO)
{
  uint8_t ret = SR04T_OK;

  if(pObj == NULL)
  {
    ret = SR04T_ERROR;
  }
  else
  {
    pObj->IO.WriteReg = pIO->WriteReg;
    pObj->IO.ReadReg  = pIO->ReadReg;

    pObj->Ctx.ReadReg  = SR04T_ReadRegWrap;
    pObj->Ctx.WriteReg = SR04T_WriteRegWrap;
    pObj->Ctx.handle   = pObj;
  }

  return ret;
}

uint16_t SR04T_u_GetDistance(SR04T_Object_t* pObj)
{
  uint16_t u_distance    = 0u;
  uint8_t  u_txBuffer[1] = { 0x55 };
  uint8_t  u_rxBuffer[4];

  SR04T_write_reg(&pObj->Ctx, u_txBuffer, 1);
  SR04T_read_reg(&pObj->Ctx, u_rxBuffer, 4);
  u_distance = ((uint16_t)u_rxBuffer[1] << 8) | (uint16_t)u_rxBuffer[2];

  return u_distance;
}

static uint32_t SR04T_ReadRegWrap(void* handle, uint8_t* pData, uint8_t Length)
{
  SR04T_Object_t* pObj = (SR04T_Object_t*)handle;

  return pObj->IO.ReadReg(pData, Length);
}

static uint32_t SR04T_WriteRegWrap(void* handle, uint8_t* pData, uint8_t Length)
{
  SR04T_Object_t* pObj = (SR04T_Object_t*)handle;

  return pObj->IO.WriteReg(pData, Length);
}

static uint32_t SR04T_read_reg(SR04T_ctx_t* ctx, uint8_t* data, uint8_t length)
{
  return ctx->ReadReg(ctx->handle, data, length);
}

static uint32_t SR04T_write_reg(SR04T_ctx_t* ctx, uint8_t* data, uint8_t length)
{
  return ctx->WriteReg(ctx->handle, data, length);
}

#ifdef __cplusplus
}
#endif
