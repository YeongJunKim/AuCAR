/*
 * queue.h
 *
 *  Created on: 2019. 6. 12.
 *      Author: colson
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "main.h"
#include "struct.h"


#ifndef BOOL
#define BOOL int
#endif

#define true 1
#define false 0



/*
uint16_t queue_size = 256;

typedef struct _queue{
  uint8_t queue[queue_size];
  int front;
  int rear;
  int count;
  int max_count;
}Q_Struct;*/


class Queue
{
  Queue();
  ~Queue();

private:
  uint8_t *queue;
  int front;
  int rear;
  int count;
  int max_count;

public:
  void init_queue(Q_Struct *str, uint16_t size);
  BOOL is_empty(Q_Struct *str);
  BOOL is_full(Q_Struct *str);
  BOOL enqueue(Q_Struct *str);
  BOOL dequeue(Q_Struct *str);

};

#endif /* QUEUE_H_ */
