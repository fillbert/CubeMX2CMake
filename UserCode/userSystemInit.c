/**
 * @file userSystemInit.c
 * @author Uladzislu Leshchanka (filbertby@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Copyright filbertby(c) 2023
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "Logger.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"

/**
 * @brief Tets task to LED flashing
 *
 * @param pvParameters  some task parameters if need
 */
void taskLedFlasher ( void * pvParameters )
{
    (void) pvParameters;

    while(1)
    {
        // some led will flash
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        //
        vTaskDelay((500 / portTICK_PERIOD_MS));
    }
}

/**
 * @brief Tets task to print out via RTT
 *
 * @param pvParameters  some task parameters if need
 */
void taskRTTOut ( void * pvParameters )
{
    (void) pvParameters;

    while(1)
    {
        // some led will flash
        uint32_t t = xTaskGetTickCount();
        LOGINFO("System Up Time is - %dh:%02dm:%02ds:%03dmS", ((t/1000)/60)/60, ((t/1000)/60)%60, (t/1000)%60, t%1000);
        (void) t;
        //
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Tets task to print out via RTT
 *
 * @param pvParameters  some task parameters if need
 */
void buttonTask ( void * pvParameters )
{
    (void) pvParameters;

    bool buttonState = true;

    while(1)
    {
        bool tmp = !!HAL_GPIO_ReadPin(BT1_GPIO_Port, BT1_Pin);
        //
        if (buttonState ^ tmp)
        {
            buttonState = tmp;
            //
            if(!buttonState)
            {
                LOGINFO("Button was pressed");
            }
            else
            {
                LOGINFO("Button was released");
            }
        }
        //
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


void userCoreInit(void)
{
    BaseType_t res = pdFALSE;

    res = xTaskCreate(taskLedFlasher, "Led Flasher", 128, NULL, 2, NULL);

    if ( pdPASS != res)
    {
        LOGERROR("Task creation was wrong!!!");
        return;
    }

    res = xTaskCreate(taskRTTOut, "RTT printout", 128, NULL, 2, NULL);

    if ( pdPASS != res)
    {
        LOGERROR("Task creation was wrong!!!");
        return;
    }

    res = xTaskCreate(buttonTask, "Button handler", 128, NULL, 2, NULL);

    if ( pdPASS != res)
    {
        LOGERROR("Task creation was wrong!!!");
        return;
    }

    /**
     * Here you have to int all your drivers and all your tasks
     */
}


