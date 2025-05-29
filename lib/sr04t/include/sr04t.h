/**********************************************************************************************************************
 * \file sr04t.h
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

#ifndef SR04T_H
#define SR04T_H

/* ============================================================================================== */
/*                                         Include Files                                          */
/* ============================================================================================== */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/*                                        Defines & Macros                                        */
/* ============================================================================================== */

/** **********************************************************************************************
 *  \brief Constants for function return values.
 *
 *  \details Defines the standard return values
 *           for SR04T-related functions.
 */
/** @{ */               /* Start SR04T return codes group */
#define SR04T_OK    (0) ///< Operation completed successfully
#define SR04T_ERROR (1) ///< Operation failed or error occurred
/** @} */               /* End SR04T return codes group */

/* ============================================================================================== */
/*                                         Public Types                                           */
/* ============================================================================================== */
typedef uint32_t (*SR04T_WriteRegFunc)(uint8_t*, uint8_t);
typedef uint32_t (*SR04T_ReadRegFunc)(uint8_t*, uint8_t);
typedef uint32_t (*SR04T_WriteFunc)(void*, uint8_t*, uint8_t);
typedef uint32_t (*SR04T_ReadFunc)(void*, uint8_t*, uint8_t);

/** **********************************************************************************************
 * \defgroup SR04T_Context SR04T Driver Context
 * \brief Data structure used to configure and access the SR04T ultrasonic sensor.
 * @{
 */

/**
 * \brief SR04T driver context structure.
 *
 * Holds function pointers for low-level register access and a device handle.
 * This context must be initialized before using the SR04T driver functions.
 */
typedef struct
{
  /**
   * \brief Function pointer to write to a device register.
   *
   * This function is called to perform register writes.
   * It should match the SR04T_WriteFunc signature defined by the driver.
   *
   * \note The implementation is platform-dependent.
   */
  SR04T_WriteFunc writeReg;

  /**
   * \brief Function pointer to read from a device register.
   *
   * This function is called to perform register reads.
   * It should match the SR04T_ReadFunc signature defined by the driver.
   *
   * \note The implementation is platform-dependent.
   */
  SR04T_ReadFunc readReg;

  /**
   * \brief Device-specific handle passed to the low-level functions.
   *
   * Typically used to pass peripheral context (e.g., I2C/SPI handle).
   * This pointer is forwarded to the `writeReg` and `readReg` functions.
   */
  void* handle;

} SR04T_CTX;

/** @} */ // end of SR04T_Context

/** **********************************************************************************************
 * \defgroup SR04T_IO_Interface SR04T Low-Level IO Interface
 * \brief Structure for low-level I/O function pointers for the SR04T ultrasonic sensor.
 * @{
 */

/**
 * \brief SR04T low-level I/O function interface.
 *
 * Contains function pointers used to perform register-level read and write operations.
 * This interface abstracts the hardware-dependent access mechanisms such as I2C or SPI.
 */
typedef struct
{
  /**
   * \brief Function pointer to write to a device register.
   *
   * Called by the driver to perform register writes.
   * Must conform to the SR04T_WriteRegFunc signature.
   *
   * \note The implementation is platform-specific.
   */
  SR04T_WriteRegFunc writeReg;

  /**
   * \brief Function pointer to read from a device register.
   *
   * Called by the driver to perform register reads.
   * Must conform to the SR04T_ReadRegFunc signature.
   *
   * \note The implementation is platform-specific.
   */
  SR04T_ReadRegFunc readReg;

} SR04T_IO;

/** @} */ // end of SR04T_IO_Interface

/** **********************************************************************************************
 * \defgroup SR04T_Object_Instance SR04T Driver Instance Object
 * \brief Structure representing a complete instance of the SR04T driver.
 * @{
 */

/**
 * \brief SR04T driver instance object.
 *
 * Represents a complete driver instance including I/O interface, context, and internal state.
 * This structure is typically used by application code to manage the SR04T driver lifecycle.
 */
typedef struct
{
  /**
   * \brief Low-level I/O interface for register access.
   *
   * Contains platform-specific read and write function pointers required to communicate
   * with the SR04T sensor at the register level.
   *
   * \see SR04T_IO
   */
  SR04T_IO io;

  /**
   * \brief Driver context structure.
   *
   * Includes function pointers and device handle used internally by the driver to
   * manage operations and maintain state.
   *
   * \see SR04T_CTX
   */
  SR04T_CTX ctx;

  /**
   * \brief Flag indicating whether the driver has been initialized.
   *
   * Value is non-zero if the driver has completed initialization; zero otherwise.
   */
  uint8_t isInitialized;

} SR04T_Object;

/** @} */ // end of SR04T_Object_Instance

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

/** **********************************************************************************************
 * \brief Initializes the SR04T driver instance.
 *
 * This function configures the driver with the provided I/O interface and prepares it
 * for operation. It sets up internal state and must be called before any other driver function.
 *
 * \param[in,out] p_obj Pointer to the SR04T_Object instance to be initialized.
 * \param[in]     p_io  Pointer to the SR04T_IO structure containing low-level I/O functions.
 *
 * \retval SR04T_OK    Initialization successful.
 * \retval SR04T_ERROR Null pointer or invalid function pointers provided.
 */
uint8_t SR04T_u_Init(SR04T_Object* p_obj, SR04T_IO* p_io);

/** **********************************************************************************************
 * \brief Measures and returns the distance detected by the SR04T sensor.
 *
 * This function triggers the measurement process and returns the measured distance in centimeters.
 *
 * \param[in] p_obj Pointer to the initialized SR04T_Object instance.
 *
 * \return Distance in centimeters (0–400). Returns 0 if measurement fails or sensor is not initialized.
 */
uint16_t SR04T_u_GetDistance(SR04T_Object* p_obj);

#ifdef __cplusplus
}
#endif

#endif // SR04T_H