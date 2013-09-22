/*
 Digit 32x16dot matrix LED module
 
 2013.6.29 by ikkei
 
*/

#ifndef Digit32x16_h
#define Digit32x16_h

#include <inttypes.h>

#define SINGLE_BUFFER 0
#define DOUBLE_BUFFER 1
#define SW_LEVEL 0
#define SW_EDGE 1


namespace Digit32x16
{
    extern void Init(uint8_t mode = SINGLE_BUFFER);
    extern void ShiftLeft();
    extern void ShiftRight();
    extern void Set(uint8_t x, uint8_t y, uint8_t c);
    extern uint8_t Get(uint8_t x, uint8_t y);
    extern volatile unsigned int tcnt2;
    extern void Flip(bool blocking = false);
    extern void Clear(int set=0);
    extern void Horizontal(int y, int set=0);
    extern void Vertical(int x, int set=0);
    extern uint8_t GetSW(uint8_t edge);
    extern uint8_t GetPeriod(void);
	extern void Vwrite(int x, uint16_t data);
    extern void write(uint8_t y, const uint8_t values[], uint8_t size);
    extern void write90(uint8_t y, const uint8_t values[], uint8_t size);
};

#endif
