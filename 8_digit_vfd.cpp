#include "Arduino.h"
#include "8_digit_vfd.h"

uint8_t slaveSelect;
uint8_t blank;
uint16_t scrollSpeed;

void VFD8DIGIT::begin(uint8_t ss, uint8_t blankPin){
	slaveSelect = ss;
	blankPin = blank;
	pinMode(slaveSelect, OUTPUT);
	digitalWrite (slaveSelect, HIGH);
	SPI.begin(); 
}

void VFD8DIGIT::vfdwrite(uint16_t dots1, uint16_t dots2, uint16_t d7, uint16_t d6, uint16_t d5, uint16_t d4, uint16_t d3, uint16_t d2, uint16_t d1, uint16_t d0){
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite(slaveSelect,LOW);
  SPI.transfer16(dots1);
  SPI.transfer16(dots2);
  SPI.transfer16(d7);
  SPI.transfer16(d6);
  SPI.transfer16(d5);
  SPI.transfer16(d4);
  SPI.transfer16(d3);
  SPI.transfer16(d2);
  SPI.transfer16(d1);
  SPI.transfer16(d0);
  digitalWrite(slaveSelect,HIGH);
  SPI.endTransaction();  
}

uint16_t VFD8DIGIT::convertChar(char c){
  switch (c){
    case '~': // degree = °
      return(0xe800);
      break;
    case ',':
      return(0x0004);
      break;
    case '?':
      return(0x4388);
      break;
    case '!':
      return(0xe802);
      break;
    case '.':
      return(0x200b);
      break;
    case '^': // apostrophe or inverted comma (for our English cousins)
      return(0x1000);
      break;
    case ' ':
      return(0x0000);
      break;
    case '_':
      return(0x0022);
      break;
    case '-':
      return(0x2200);
      break;
    case '*':
      return(0x3e1c);
      break;
    case '/':
      return(0x0404);
      break;
    case '`': // backslash
      return(0x1010);
      break;
    case '@': // @
      return(0xc3e9);
      break;
    case '$': // $
      return(0xeb6a);
      break;
    case '%': // %
      return(0xee6c);
      break;
    case '&': // &
      return(0x2bb3);
      break;
    case '<': // (
      return(0x0410);
      break;
    case '>': // )
      return(0x1004);
      break;
    case '[': // [
      return(0x0928);
      break;
    case ']': // ]
      return(0x480a);
      break;
    case '|': // |
      return(0x0808);
      break;
    case '0':
      return(0xc5e7);
      break;
    case '1':
      return(0x482a);
      break;
    case '2':
      return(0x63a3);
      break;
    case '3':
      return(0x4762);
      break;
    case '4':
      return(0xa2c0);
      break;
    case '5':
      return(0xe362);
      break;
    case '6':
      return(0xe363);
      break;
    case '7':
      return(0x41c0);
      break;
    case '8':
      return(0xe3e3);
      break;
    case '9':
      return(0xe3e2);
      break;
    case 'A':
      return(0xe3c1);
      break;
    // case 'B':
    //   return(0xa263);
    //   break;
    case 'B':
      return(0xea63);
      break;
    case 'C':
      return(0xc123);
      break;
    case 'D':
      return(0x22e3);
      break;
    case 'E':
      return(0xe123);
      break;
    case 'F':
      return(0xe101);
      break;
    case 'G':
      return(0xc363);
      break;
    case 'H':
      return(0xa2c1);
      break;
    case 'I':
      return(0x492a);
      break;
    case 'J':
      return(0x00e3);
      break;
    case 'K':
      return(0x0c18);
      break;
    case 'L':
      return(0x8023);
      break;
    case 'M':
      return(0x94c1);
      break;
    case 'N':
      return(0x90d1);
      break;
    case 'O':
      return(0xc1e3);
      break;
    case 'P':
      return(0xe381);
      break;
    case 'Q':
      return(0xc1f3);
      break;
    case 'R':
      return(0xe391);
      break;
    case 'S':
      return(0xe362);
      break;
    case 'T':
      return(0x4908);
      break;
    case 'U':
      return(0x80e3);
      break;
    case 'V':
      return(0x8405);
      break;
    case 'W':
      return(0x80d5);
      break;
    case 'X':
      return(0x1414);
      break;
    case 'Y':
      return(0x1408);
      break;
    case 'Z':
      return(0x4526);
      break;
  }
};

void VFD8DIGIT::displayScrollingMessage(String displayText, uint16_t scrollSpeed){
	String message;// = displayText;
	String slide_in = "        ";
	String exit_gracefully = "         ";
	message = slide_in+displayText+exit_gracefully;
	message.toUpperCase();                              // change all to upper case so the switch case werx
	char letters[message.length()];                     // make array of chars of length of the message
	message.toCharArray(letters, message.length());     // put the message into the array of chars called letters
	uint16_t hexLetters[message.length()];              // create empty array of 16 bit uints

	int i = 0;
	for(i;i<(message.length()-1);i++){              // create an index n elements long
		hexLetters[i]=convertChar(letters[i]);            // send letters one by one to character mapping switch case
	}
  int n = message.length();
	int x = 0;
	while(1){ // stay here forever
		vfdwrite(0,0,hexLetters[x+0],hexLetters[x+1],
      hexLetters[x+2],hexLetters[x+3],hexLetters[x+4],
      hexLetters[x+5],hexLetters[x+6],hexLetters[x+7]);
			x+=1;
			if(x==(n-8)){
				x=0;
			}
		delay(scrollSpeed);
	}
};

void VFD8DIGIT::displayStaticMessage(String displayText){
  String message;                                     // = displayText;
  String emptyChar = " ";
  message = displayText + emptyChar;
  message.toUpperCase();                              // change all to upper case so the switch case werx
  char letters[message.length()];                     // make array of chars of length of the message
  message.toCharArray(letters, message.length());     // put the message into the array of chars called letters
  uint16_t hexLetters[message.length()];              // create empty array of 16 bit uints

  int i = 0;
  for(i;i<(message.length());i++){                    // create an index n elements long
    hexLetters[i]=convertChar(letters[i]);            // send letters one by one to character mapping switch case
  }

  if(message.length()<9){
    i-=1;
    for(i;i<9;i++){
     hexLetters[i]=0;
    }
  }

  uint8_t x = 0;
  vfdwrite(0,0,hexLetters[x+0],hexLetters[x+1],
      hexLetters[x+2],hexLetters[x+3],hexLetters[x+4],
      hexLetters[x+5],hexLetters[x+6],hexLetters[x+7]);

};

// 3 levels: 1=dim 2=med 3=bright
void VFD8DIGIT::setBrightness(uint8_t mode){
	if(mode<1)mode=1;
	if(mode>3)mode=3;
	analogWrite(blank,mode);
};