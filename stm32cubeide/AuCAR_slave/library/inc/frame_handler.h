/*
 * frame_handler.h
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */

#ifndef FRAME_HANDLER_H_
#define FRAME_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DEVICE_STM32F446RE_C1 0x01
#define DEVICE_STM32F446RE_C2 0x02
#define DEVICE_STM32F446RE_C3 0x03

#ifdef DEVICE_TYPE
#error "Device is not selected."
#else
#if DEVICE_TYPE == DEVICE_STM32F446RE_C1 /**< slave 1 */

#elif DEVICE_TYPE == DEVICE_STM32F446RE_C2 /**< slave 2 */

#elif DEVICE_TYPE == DEVICE_STM32F446RE_C3 /**< master */

#endif
#endif


#define SEQ_READY 	0x00
#define SEQ_START 	0x01
#define SEQ_CMD1 	0x02
#define SEQ_CMD2 	0x03
#define SEQ_LEN 	0x04
#define SEQ_GET 	0x05
#define CEHCK_SUM 	0x06

typedef struct _dataFrame
{
	uint8_t idle[2];		/**< start header -> (0xFF, 0xFF)  */
	uint16_t cmd;			/**< command */
	uint8_t len;			/**< data length */
	uint8_t *data;			/**< data pointer */
	uint8_t checksum;		/**< data checksum */
}dataFrame_ST;


void frame_init(dataFrame_ST* frame);
void frame_set_message(dataFrame_ST* frame, uint16_t cmd, uint16_t sid, uint16_t did, uint8_t len, uint8_t *data);
void frame_reset_message(dataFrame_ST* frame);

void frame_get_message_sequence_uart(dataFrame_ST* frame, uint8_t data);
void frame_rx_cplt_Callback(dataFrame_ST* frame);


#ifdef __cplusplus
}
#endif
#endif /* FRAME_HANDLER_H_ */
