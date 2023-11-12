/**
 * @file ETM_Init.c
 * @author Uladzislu Leshchanka (filbertby@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-22
 *
 * @copyright Copyright filbertby(c) 2026
 *
 */
#include <stdint.h>

/**
 * @brief Initialize the SWO (Serial Wire Output) interface.
 *
 * @param mask Bitmask to configure the SWO ports.
 */
 void SWO_Init( uint32_t mask );


 /**
  * @brief Send a character via the ITM (Instrumentation Trace Macrocell) interface.
  *
  * @param c Character to send.
  */
 void ITM_SendCharInline(char c);

