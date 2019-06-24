/*
 * frame_handler.c
 *
 *  Created on: Jun 22, 2019
 *      Author: colson
 */


#include "frame_handler.h"




void frame_init(dataFrame_ST* frame)
{
	frame->idle[0] = 0xFF;
	frame->idle[1] = 0xFF;
	frame->cmd = 0x0000;
	frame->len = 0;
	frame->data = 0;
	frame->checksum = 0;
}

void frame_set_message(dataFrame_ST* frame, uint16_t cmd, uint16_t sid, uint16_t did, uint8_t len, uint8_t *data)
{

}

void frame_reset_message(dataFrame_ST* frame)
{

}

void frame_get_message_sequence_uart(dataFrame_ST* frame, uint8_t data)
{

}

__weak void frame_rx_cplt_Callback(dataFrame_ST* frame)
{

}
