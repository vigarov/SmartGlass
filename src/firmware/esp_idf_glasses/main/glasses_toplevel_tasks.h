#pragma once

const char* toplevel_tasks_BLE_tag = "BLE_task";
const char* toplevel_tasks_Display_tag = "Display_task";
const char* toplevel_tasks_GNSS_tag = "GNSS_task";

/**
 * @brief Task in charge of handling the bluetooth.
 * @arg pvParameters (void *) pointer to context parameters. Unused
 */
void T_HandleBLE( void *pvParameters);

void T_Display(void* pvParameters);


void T_GNSS_Task(void *pvParameters);
