/**
 * @file Logger.c
 * @author Uladzislu Leshchanka (filbertby@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright filbertby(c) 2023
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include "Logger.h"
#include <SEGGER_RTT.h>
#include "ETM_init.h"

/**
 * @brief   stub if we not implemented this function
 *          or do not use FreeRTOS
 */
__attribute__((weak)) uint32_t xTaskGetTickCount( void )
{
    return 0;
}

#if CONFIG_DEBUG_IFACE_SEGGER

/**
 * @brief Print RTT Log Output
 *
 * @param e Debug Level
 * @param format Debut output
 * @param ... all another arguments
 */
void mLogger ( const char * e, const char * format, ...)
{
    // print header
    SEGGER_RTT_printf(0, "%010d%s",  xTaskGetTickCount(), e);

    // print body
    va_list args;
    va_start(args, format);
    SEGGER_RTT_vprintf(0, format, &args);
    va_end(args);

    // print footer
    SEGGER_RTT_printf(0, "\n\r");
}

#endif

#if CONFIG_DEBUG_IFACE_STLINK


void ITM_Print(const char *s)
{
    while (*s)
        ITM_SendCharInline(*s++);
}

void ITM_vprintf(const char *fmt, va_list args)
{
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    ITM_Print(buffer);
}

void ITM_printf(const char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    ITM_Print(buffer);
}

void mLogger(const char *e, const char *format, ...)
{
    // print header
    ITM_printf("%010lu%s", xTaskGetTickCount(), e);

    // print body
    va_list args;
    va_start(args, format);
    ITM_vprintf(format, args);
    va_end(args);

    // print footer
    ITM_Print("\n\r");
}
#endif