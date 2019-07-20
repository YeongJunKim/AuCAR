/*
 * AuCAR_conf.h
 *
 *  Created on: Jun 23, 2019
 *      Author: colson
 */

#ifndef INC_AUCAR_CONF_H_
#define INC_AUCAR_CONF_H_

#define C1 0x01
#define C2 0x02
#define C3 0x03

#define LOCAL_DEVICE C1

#ifndef LOCAL_DEVICE
#error "LOCAL_DEVICE NOT DEFINED!"
#define LOCAL_DEVICE = 0x00

#else
#if LOCAL_DEVICE == C1

#elif LOCAL_DEVICE == C2

#elif LOCAL_DEVICE == C3

#endif
#endif



#define C3_LED 			0x01
#define C3_LED_ALT 		0x02
#define LED_TYPE C3_LED

#define C3_MAX_DIR 		0x01
#define C3_MAX_DIR_ALT 	0x02
#define MAX_DIR_TYPE C3_MAX_DIR

#endif /* INC_AUCAR_CONF_H_ */
