/**
 * @file Logger.h
 * @author Uladzislu Leshchanka (filbertby@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright filbertby(c) 2023
 *
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "autoconf.h"

// Logger function
void mLogger(const char * e, const char * format, ...);


#if defined (CONFIG_DEBUG_IFACE_SEGGER) && defined (CONFIG_TEST_APP_DEBUG)

    /** Macro to log an error message */
    #define LOGERROR(format, ...)            mLogger("[E]", format, ##__VA_ARGS__)

    /** Macro to log a warning message */
    #define LOGWARN(format, ...)             mLogger("[W]", format, ##__VA_ARGS__)

    /** Macro to log an informational message */
    #define LOGINFO(format, ...)             mLogger("[I]", format, ##__VA_ARGS__)

    /** Macro to log a debug message */
    #define LOGDEBUG(format, ...)            mLogger("[D]", format, ##__VA_ARGS__)

#else

    #define LOGERROR(format, ...)   {}
    #define LOGWARN(format, ...)    {}
    #define LOGINFO(format, ...)    {}
    #define LOGDEBUG(format, ...)   {}

#endif

#endif // _LOGGER_H_