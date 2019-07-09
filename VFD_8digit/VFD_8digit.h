#ifndef VFD_8digit_h
#define VFD_8digit_h

#include "Arduino.h"
#include <SPI.h>

class VFD8DIGIT {
	public:

		// define slave select/load pin and blank pin
		void begin(uint8_t ss, uint8_t blankPin);
		// 3 levels of brightness
		void setBrightness(uint8_t mode);
		// message from user
		void displayScrollingMessage(String displayText, uint16_t scrollSpeed);
		void displayStaticMessage(String displayText);
		// decode char for required vfd pins
		uint16_t convertChar(char c);
		// shift out 160 bits to the tubes
		void vfdwrite(uint16_t dots1, uint16_t dots2, 
			uint16_t d7, uint16_t d6, uint16_t d5, 
			uint16_t d4, uint16_t d3, uint16_t d2, 
			uint16_t d1, uint16_t d0);
	
};

#endif