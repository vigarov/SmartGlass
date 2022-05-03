#pragma once

/**
 * @brief Task in charge of handling the bluetooth.
 * @arg pvParameters (void *) pointer to context parameters. Unused
 */
void T_HandleBLE( void *pvParameters);

void T_Display(void* pvParameters);


void T_GNSS_Task(void *pvParameters);
