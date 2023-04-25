/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

#define TASK_EDBG_COM_STACK_SIZE (300 / sizeof(portSTACK_TYPE))
#define TASK_EDBG_COM_STACK_PRIORITY (tskIDLE_PRIORITY + 1)

static TaskHandle_t xCreatededbg_comTask;
static uint8_t      example_EDBG_COM[12] = "Hello World!";

/**
 * Example task of using EDBG_COM to echo using the IO abstraction.
 */
static void EDBG_COM_example_task(void *param)
{
	struct io_descriptor *io;
	uint16_t              data;

	(void)param;

	usart_os_get_io(&EDBG_COM, &io);
	io_write(io, example_EDBG_COM, 12);

	for (;;) {
		if (io_read(io, (uint8_t *)&data, 2) == 2) {
			io_write(io, (uint8_t *)&data, 2);
		}
		os_sleep(10);
	}
}

/**
 * \brief Create OS task for EDBG_COM
 */
void task_edbg_com_create()
{
	/* Create task for EDBG_COM */
	if (xTaskCreate(EDBG_COM_example_task,
	                "edbg_com",
	                TASK_EDBG_COM_STACK_SIZE,
	                NULL,
	                TASK_EDBG_COM_STACK_PRIORITY,
	                &xCreatededbg_comTask)
	    != pdPASS) {
		while (1) {
			/* Please checkup stack and FreeRTOS configuration. */
		}
	}
	/* Call vTaskStartScheduler() function in main function. Place vTaskStartScheduler function call after creating all
	 * tasks and before while(1) in main function */
}
