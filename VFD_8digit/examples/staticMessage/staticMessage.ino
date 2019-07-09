/*********************************************************************
This example will display the message from left to right.
If the message is longer than 8 digits/characters anything past the 8th
digit will not be displayed.

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
  // only one version of sayThisNow should be uncommented at a time, try the second
  String sayThisNow = "hi mom";
  
  // try the following version to see the message cutoff described at the top of this example
  //String sayThisNow = "hello mom";

  // send the message
  vfd.displayStaticMessage(sayThisNow);

}

void loop() {

}