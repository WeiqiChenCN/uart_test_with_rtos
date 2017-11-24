#include <string.h>
#include <kfifo.h>

typedef unsigned int uint;

static inline uint min( uint x, uint y ){
	return (x < y ? x : y);
}


void kfifo_init( struct kfifo *fifo, uint8_t *buff, unsigned int size ){
	fifo->in = 0;
	fifo->out = 0;
	fifo->size = size;
	fifo->buff = buff;
}

static void kfifo_copy_out( struct kfifo *fifo, uint8_t *dst, uint len, uint off ){
	uint size = fifo->size;
	uint mask = fifo->size - 1;
	uint l;
	off &= mask;
	l = min(len, size-off);
	memcpy(dst, fifo->buff+off, l );
	memcpy(dst+l, fifo->buff, len-l );
}

static inline uint __kfifo_out_peek( struct kfifo *fifo, void *buff, uint len ){
	uint l;
	l = fifo->in - fifo->out;
	if(len>l)
		len = l;
	kfifo_copy_out(fifo, buff, len, fifo->out);
	return len;
}

uint kfifo_out( struct kfifo *fifo, char *buff, unsigned int len ){
	len = __kfifo_out_peek( fifo, buff, len );
	fifo->out += len;
	return len;
}



static inline unsigned int kfifo_unused( const struct kfifo *fifo ){
	return fifo->size - (fifo->in - fifo->out);
}

static void kfifo_copy_in( struct kfifo *fifo, const uint8_t *src, uint len, uint off ){
	uint size = fifo->size;
	uint mask = size - 1;
	uint l;
	
	off &= mask;
	l = min(len, size-off);
	memcpy(fifo->buff+off, src, l );
	memcpy(fifo->buff, src+l, len-l );
}

uint kfifo_in( struct kfifo *fifo, const char *buff, unsigned int len ){
	uint l;
	l = kfifo_unused(fifo);
	if(len>l)
		len = l;
	kfifo_copy_in( fifo, (const uint8_t*)buff, len, fifo->in );
	fifo->in += len;
	return len;
}


bool is_kfifo_empty( const struct kfifo *fifo ){
	return ( kfifo_unused(fifo)==fifo->size );
	
}
bool is_kfifo_full( const struct kfifo *fifo ){
	return ( kfifo_unused(fifo)==0 );
}
