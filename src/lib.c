#include <stddef.h>
#include <stdint.h>

void *memset(void *s, int c, size_t n)
{
	void *p = s;

	while(n--)
		*(int *)p++ = c;

	return s;
}

void *memset16(void *s, uint16_t c, size_t n)
{
	uint16_t *p = s;

	while(n--)
		*p++ = c;

	return s;
}

size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
