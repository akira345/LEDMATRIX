/*
 Digit 32x16dot matrix LED module
 
 2013.6.29 by ikkei
 
*/


//#include "WProgram.h" // for Arduino 022-
#include <arduino.h> // for Arduino 1.0
#include <inttypes.h>
#include <avr/interrupt.h>
#include <Digit32x16.h>
#include <MsTimer2.h>


const int sin1 = 2;
const int sin2 = 3;
const int sin3 = 4;
const int clock = 5;
const int latch = 6;
const int disable = 7;


/* -----------------------------------------------------------------  */
/** Table for the LED multiplexing cycles, containing 16 cycles made out of three bytes
*/

uint16_t leds[2][32];

/// Determines whether the display is in single or double buffer mode
uint16_t displayMode;

/// Flag indicating that the display page should be flipped as soon as the
/// current frame is displayed
boolean videoFlipPage;

/// Pointer to the buffer that is currently being displayed
uint16_t* displayBuffer;

/// Pointer to the buffer that should currently be drawn to
uint16_t* workBuffer;

//boolian frame = false; //frame, 10ms, 100ms


static uint8_t sw1234;
static uint8_t swdata;
static uint8_t period;
static uint8_t current_sw;
static uint8_t previous_sw;
static uint8_t scan;// 16 Cycles of Matrix
static uint8_t msec;

//###
#define FRAME 0x01
#define TENMS 0x02


/* -----------------------------------------------------------------  */
/** The Interrupt code goes here !  
 */
void scanLED(){
	// output one line
	for (byte i = 0; i<16; i++){
		if (scan == i){
			digitalWrite(sin1, HIGH );
		} else {
			digitalWrite(sin1,LOW );
		}
		digitalWrite(sin2, (displayBuffer[scan*2   ] >> i) & 0x01 );
		digitalWrite(sin3, (displayBuffer[scan*2 +1] >> i) & 0x01 );
		digitalWrite(clock, HIGH);
		digitalWrite(clock, LOW);
	}
	digitalWrite(latch, HIGH);
	digitalWrite(latch, LOW);

	period = 0;
	msec++;
	if (msec >= 10){
		msec = 0;
		period |= TENMS;
	}
	
	scan++;
	if (scan >= 16){
		scan = 0;
		period |= FRAME;

		// If the page should be flipped, do it here.
		if (videoFlipPage && displayMode == DOUBLE_BUFFER){
		    // TODO: is this an atomic operation?
		    videoFlipPage = false;

		    uint16_t* temp = displayBuffer;
		    displayBuffer = workBuffer;
		    workBuffer = temp;
		}
	}
}


/* -----------------------------------------------------------------  */
/** Constructor : Initialize the interrupt code. 
 * should be called in setup();
 */
void Digit32x16::Init(uint8_t mode){
	digitalWrite(disable, HIGH); // All LED off
	//### MsTimer2 setting
	MsTimer2::set(1,scanLED);
	MsTimer2::start();

	// Record whether we are in single or double buffer mode
	displayMode = mode;

	// Point the display buffer to the first physical buffer
	displayBuffer = leds[0];

	// If we are in single buffered mode, point the work buffer
	// at the same physical buffer as the display buffer.  Otherwise,
	// point it at the second physical buffer.
	if( displayMode == SINGLE_BUFFER ) {
	    workBuffer = displayBuffer;
	}else {
	    workBuffer = leds[1];
	}

	scan = 0;
	msec = 0;
	
	pinMode(sin1, OUTPUT);
	pinMode(sin2, OUTPUT);
	pinMode(sin3, OUTPUT);
	pinMode(clock, OUTPUT);
	pinMode(latch, OUTPUT);
	pinMode(disable, OUTPUT);

	// Clear the buffer and display it
	Digit32x16::Clear(0);
	Digit32x16::Flip(false);
	digitalWrite(disable, LOW); // LED on
}


/* -----------------------------------------------------------------  */
/* * Clear the screen completely
 * @param blocking if true : wait for flip before returning, if false :
 *                 return immediately.
 */
void Digit32x16::Flip(bool blocking){
    if (displayMode == DOUBLE_BUFFER){
        // Just set the flip flag, the buffer will flip between redraws
        videoFlipPage = true;

        // If we are blocking, sit here until the page flips.
        while (blocking && videoFlipPage) {
            delay(1);
        }
    }
}


/* -----------------------------------------------------------------  */
/** Clear the screen completely
 * @param set if 1 : make all led ON, if not set or 0 : make all led OFF
 */
void Digit32x16::Clear(int set) {
    for(int x=0;x<32;x++)  
        for(int y=0;y<16;y++) 
            Set(x,y,set);
}

/* -----------------------------------------------------------------  */
/** Shift left the screen completely
 */
void Digit32x16::ShiftLeft() {
    for(int x=1;x<32;x++)  
        for(int y=0;y<16;y++) 
            Set(x-1,y,Get(x,y));
}

/* -----------------------------------------------------------------  */
/** Shift right the screen completely
 */
void Digit32x16::ShiftRight() {
    for(int x=1;x<32;x++)  
        for(int y=0;y<16;y++) 
            Set(32-x,y,Get(31-x,y));
}

/* -----------------------------------------------------------------  */
/** Clear an horizontal line completely
 * @param y is the y coordinate of the line to clear/light [0-8]
 * @param set if 1 : make all led ON, if not set or 0 : make all led OFF
 */
void Digit32x16::Horizontal(int y, int set) {
    for(int x=0;x<32;x++)  
        Set(x,y,set);
}


/* -----------------------------------------------------------------  */
/** Clear a vertical line completely
 * @param x is the x coordinate of the line to clear/light [0-13]
 * @param set if 1 : make all led ON, if not set or 0 : make all led OFF
 */
void Digit32x16::Vertical(int x, int set) {
    for(int y=0;y<16;y++)  
        Set(x,y,set);
}

/* -----------------------------------------------------------------  */
void Digit32x16::Vwrite(int x, uint16_t data) {
    for(int y=0; y<16; y++){
    	Set(x, y, bitRead(data, y));
    }
}


/* -----------------------------------------------------------------  */
void Digit32x16::write(uint8_t y, const uint8_t values[], uint8_t size){
	for(uint8_t i=0;i<size;i++){
		for(uint8_t j=0;j<8;j++){
			Set((i%4)*8+j, ((y+i/4)%16), bitRead( values[i],7-j));
		}
	}
}

/* -----------------------------------------------------------------  */
void Digit32x16::write90(uint8_t y, const uint8_t values[], uint8_t size){
	for(uint8_t i=0;i<size;i++){
		for(uint8_t j=0;j<8;j++){
			Set(i/2, (1-i%2)*8+j,   bitRead( values[i],j));
		}
	}
}

/* -----------------------------------------------------------------  */
void Digit32x16::Set(uint8_t x, uint8_t y, uint8_t c){
	if (c == 1) {
		if ( x < 16 ){
		    bitSet(  workBuffer[ y*2     ], 15 - x);
		}else{
		    bitSet(  workBuffer[ y*2 + 1 ], 31 - x);
		}
	} else {
		if ( x < 16 ){
		    bitClear(workBuffer[ y*2     ], 15 - x);
		}else{
		    bitClear(workBuffer[ y*2 + 1 ], 31 - x);
		}
	}
}

/* -----------------------------------------------------------------  */
uint8_t Digit32x16::Get(uint8_t x, uint8_t y){
	uint8_t b;

	if ( x < 16 ){
		b = bitRead(workBuffer[ y*2     ], 15 - x);
	}else{
		b = bitRead(workBuffer[ y*2 + 1 ], 31 - x);
	}
	return b;
}


/* -----------------------------------------------------------------  */
/** GetSW : get switch status
 */
uint8_t Digit32x16::GetSW(uint8_t edge){
 	return (0);
} 


/* -----------------------------------------------------------------  */
/** GetPeriod : get period flag
 */
uint8_t Digit32x16::GetPeriod(void)
{
	static uint8_t previous_period;
	uint8_t flag = period & ~previous_period;
	previous_period = period;

 	return (flag);
} 


