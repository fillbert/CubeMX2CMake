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
#include "main.h"
#include "ETM_init.h"
#include "autoconf.h"


#if defined (CONFIG_DEBUG_IFACE_STLINK) && defined (CONFIG_TEST_APP_DEBUG)
void SWO_Init( uint32_t mask )
{
    /// Enable trace subsystem
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Enable TRACESWO
    DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;

    // TPIU / SWO config
    TPI->CSPSR = 1;   // 1-bit port
    TPI->ACPR  = (HAL_RCC_GetHCLKFreq() / 4000000U) - 1U; // 4 MHz SWO
    TPI->SPPR  = 2;   // NRZ / UART mode

    // Optional but often useful
    TPI->FFCR = 0x00000100; // disable formatter / stop on flush depending on core

    // Unlock ITM
    ITM->LAR = 0xC5ACCE55;

    // Enable ITM
    ITM->TCR = ITM_TCR_ITMENA_Msk |
               ITM_TCR_SWOENA_Msk |
               ITM_TCR_TSENA_Msk  | // TSENA only if timestamps really needed
               ITM_TCR_DWTENA_Msk;

    ITM->TPR = mask;   // allow unprivileged access to all ports if needed
    ITM->TER = mask;   // enable all 32 stimulus ports
}


void ITM_SendCharInline(char c)
{
    if (ITM->TCR & ITM_TCR_ITMENA_Msk)          // ITM enabled?
    {
        if (ITM->TER & (1UL << 0))              // Port 0 enabled?
        {
            while (ITM->PORT[0].u32 == 0);      // Wait for readiness
            ITM->PORT[0].u8 = (uint8_t)c;       // Send char
        }
    }
}
#else
/**
 * @brief   stub if SWO is disabled for current build config.
 */
__attribute__((weak)) void SWO_Init( uint32_t mask )
{
    (void) mask;
}
#endif