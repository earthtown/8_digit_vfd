/*********************************************************************
This example uses the scrolling message function to demo the symbols,
characters, and numbers included in the library.

Written by brandon dunson (brandon.dunson at klangelectronics.com)
on July 8th, 2019 to be used with our
8 digit Russian VFD (IV-4) display assembly.
*********************************************************************/

#include "VFD_8digit.h"

VFD8DIGIT vfd;

void setup() {

  // crank up the vfds and send load pin and blank pin (LOAD,BLANK)  
  vfd.begin(10,6);

  // all the standard symbols, numbers, and characters in the library
  String sayThisNow = ".~,^/`*-_|@$%&<>[]0123456789abcdefghijklmnopqrstuvwxyz";

  // send the message and elapsed time between shifting letters to the left (in milliseconds)
  vfd.displayScrollingMessage(sayThisNow, 500);

}

void loop() {

}