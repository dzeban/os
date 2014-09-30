#ifndef _LIB_H
#define _LIB_H

#include <stddef.h>
#include <stdint.h>

void *memset(void *s, int c, size_t n);
void *memset16(void *s, uint16_t c, size_t n);
size_t strlen(const char* str);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif // _LIB_H
