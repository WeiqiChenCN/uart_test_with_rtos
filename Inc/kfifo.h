#ifndef __KFIFO_H__
#define __KFIFO_H__

#include <stdint.h>
#include <stdbool.h>

struct kfifo {
	unsigned int	in;
	unsigned int	out;
	unsigned int	size;
	uint8_t *		  buff;
};

unsigned int kfifo_in( struct kfifo *fifo, const char *buff, unsigned int len );
unsigned int kfifo_out( struct kfifo *fifo, char      *buff, unsigned int len );
void kfifo_init( struct kfifo *fifo, uint8_t *buff, unsigned int size );
bool is_kfifo_empty( const struct kfifo *fifo );
bool is_kfifo_full( const struct kfifo *fifo );

#endif//__KFIFO_H__
