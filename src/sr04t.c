/**********************************************************************************************************************
 * \file sr04t.c
 *
 * \author MarcoAAG
 *
 * \date May-03-2025
 *
 * \version 1.0 \n \n
 *
 * \brief Implementation of the SR04T driver
 *
 *********************************************************************************************************************/

/* ============================================================================================== */
/*                                         Include Files                                          */
/* ============================================================================================== */
#include <sr04t.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/*                                    Private Function Prototypes                                 */
/* ============================================================================================== */

/** **********************************************************************************************
 * \defgroup SR04T_Private_IO Internal Register Access Wrappers
 * \brief Internal static functions used to abstract register-level read/write operations.
 * @{
 */

/**
 * \brief Wrapper function to perform a register read using SR04T_Object.
 *
 * Forwards the read request to the function pointer defined in the `SR04T_IO` interface.
 *
 * \param[in]  p_handle Pointer to the SR04T_Object instance (cast to void*).
 * \param[out] p_data   Pointer to the buffer where data will be stored.
 * \param[in]  u_length Number of bytes to read.
 *
 * \return Status code returned by the underlying `readReg` function.
 */
static uint32_t SR04T_ReadRegWrap(void* p_handle, uint8_t* p_data, uint8_t u_length);

/**
 * \brief Wrapper function to perform a register write using SR04T_Object.
 *
 * Forwards the write request to the function pointer defined in the `SR04T_IO` interface.
 *
 * \param[in] p_handle Pointer to the SR04T_Object instance (cast to void*).
 * \param[in] p_data   Pointer to the buffer containing data to write.
 * \param[in] u_length Number of bytes to write.
 *
 * \return Status code returned by the underlying `writeReg` function.
 */
static uint32_t SR04T_WriteRegWrap(void* p_handle, uint8_t* p_data, uint8_t u_length);

/**
 * \brief Performs a register read through the driver context.
 *
 * Uses the read function and handle stored in the `SR04T_CTX` to perform the operation.
 *
 * \param[in]  p_ctx    Pointer to the SR04T_CTX structure.
 * \param[out] p_data   Pointer to the buffer where data will be stored.
 * \param[in]  u_length Number of bytes to read.
 *
 * \return Status code returned by the context's `readReg` function.
 */
static uint32_t SR04T_read_reg(SR04T_CTX* p_ctx, uint8_t* p_data, uint8_t u_length);

/**
 * \brief Performs a register write through the driver context.
 *
 * Uses the write function and handle stored in the `SR04T_CTX` to perform the operation.
 *
 * \param[in] p_ctx    Pointer to the SR04T_CTX structure.
 * \param[in] p_data   Pointer to the buffer containing data to write.
 * \param[in] u_length Number of bytes to write.
 *
 * \return Status code returned by the context's `writeReg` function.
 */
static uint32_t SR04T_write_reg(SR04T_CTX* p_ctx, uint8_t* p_data, uint8_t u_length);

/** @} */ // end of SR04T_Private_IO

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

uint8_t SR04T_u_Init(SR04T_Object* p_obj, SR04T_IO* p_io)
{
  uint8_t u_ret = SR04T_OK;

  if(p_obj == NULL)
  {
    u_ret = SR04T_ERROR;
  }
  else
  {
    p_obj->io.writeReg = p_io->writeReg;
    p_obj->io.readReg  = p_io->readReg;

    p_obj->ctx.readReg  = SR04T_ReadRegWrap;
    p_obj->ctx.writeReg = SR04T_WriteRegWrap;
    p_obj->ctx.handle   = p_obj;
  }

  return u_ret;
}

uint16_t SR04T_u_GetDistance(SR04T_Object* p_obj)
{
  uint16_t u_distance    = 0u;
  uint8_t  a_txBuffer[1] = { 0x55 };
  uint8_t  a_rxBuffer[4];

  SR04T_write_reg(&p_obj->ctx, a_txBuffer, 1);
  SR04T_read_reg(&p_obj->ctx, a_rxBuffer, 4);
  u_distance = ((uint16_t)a_rxBuffer[1] << 8) | (uint16_t)a_rxBuffer[2];

  return u_distance;
}

/* ============================================================================================== */
/*                                         Private Functions                                      */
/* ============================================================================================== */

static uint32_t SR04T_ReadRegWrap(void* p_handle, uint8_t* p_data, uint8_t u_length)
{
  SR04T_Object* p_obj = (SR04T_Object*)p_handle;

  return p_obj->io.readReg(p_data, u_length);
}

static uint32_t SR04T_WriteRegWrap(void* p_handle, uint8_t* p_data, uint8_t u_length)
{
  SR04T_Object* p_obj = (SR04T_Object*)p_handle;

  return p_obj->io.writeReg(p_data, u_length);
}

static uint32_t SR04T_read_reg(SR04T_CTX* p_ctx, uint8_t* p_data, uint8_t u_length)
{
  return p_ctx->readReg(p_ctx->handle, p_data, u_length);
}

static uint32_t SR04T_write_reg(SR04T_CTX* p_ctx, uint8_t* p_data, uint8_t u_length)
{
  return p_ctx->writeReg(p_ctx->handle, p_data, u_length);
}

#ifdef __cplusplus
}
#endif
