/*
 * struct.h
 *
 *  Created on: 2019. 6. 12.
 *      Author: colson
 */

#ifndef STRUCT_H_
#define STRUCT_H_

#include "main.h"
//can type


typedef struct _can_type{

}can_type;
//uart type
typedef struct _uart_type{

}uart_type;



typedef struct _data_structure{
  //common frame
  uint8_t *header;
  uint8_t *data;
  uint8_t checksum;

  //for can frame
  uint8_t cmd;
  uint8_t sid;
  uint8_t did;
  uint8_t data[8];

  uint8_t len;
}data_struct;



#endif /* STRUCT_H_ */
