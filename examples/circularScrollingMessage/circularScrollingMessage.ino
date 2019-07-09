/*********************************************************************
This example will scroll the message into the VFDs from right to left.
When all of the text been displayed and scrolled through there will 
be a noticable absence of text (9 digits blank to be exact) to show
viewers that the message is starting over.

Written by brandon dunson (brandon.dunson at klangelectronics.com)
on July 8th, 2019 to be used with our
8 digit Russian VFD (IV-4) display assembly.
*********************************************************************/

#include "VFD_8digit.h"

VFD8DIGIT vfd;

void setup() {

  // crank up the vfds and send load pin and blank pin (LOAD,BLANK)  
  vfd.begin(10,6);

  // store the desired message in a string, obvs this should be a loving message to mom
  String sayThisNow = "i love you mom";

  // send the message and elapsed time between shifting letters to the left (in milliseconds)
  vfd.displayScrollingMessage(sayThisNow, 200);

}

void loop() {

}