#include "fifo.h"

void fifo8_init(struct FIFO8 *fifo, int size, unsigned char *buf) {
  fifo->size = size;
  fifo->buf = buf;
  fifo->free = size;
  fifo->flags = 0;
  fifo->next_