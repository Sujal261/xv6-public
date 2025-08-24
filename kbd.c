#include "types.h"
#include "x86.h"
#include "defs.h"
#include "kbd.h"

int
kbdgetc(void)
{
  static uint shift; //a bitmask that tracks which modifiers are active like shift, ctrl , alt , capslock, eoesc
  static uchar *charcode[4] = {
    normalmap,//for normal keypresses
    shiftmap,//keys  with shift pressed 
    ctlmap,//keys with ctrl pressed
    ctlmap // used for certain cobinations
  };//look up table for translating scancodes into characters
  uint st, data, c;

  st = inb(KBSTATP);//reads the status byte from the keyboard
  if((st & KBS_DIB) == 0)//here kbs dib means data in buffer if not set no key press data is ready
    return -1;
  data = inb(KBDATAP);//reads the scancode from the data port
 
  if(data == 0xE0){ // 0xE0 means next scancode belongs to an extended key (eg arrow , right ctrl , etc)
    shift |= E0ESC; // it sets the e0esc flag so we remember that the next byte shoyuld be treated differently 
    return 0; // we dont yet produce the a character we are just preparing for the next scancode 
  } else if(data & 0x80){ // here data & 0x80 keeps track of is the key pressed or the key is released if msb =0 key is pressed if msb = 1 key is released
    // Key released
    data = (shift & E0ESC ? data : data & 0x7F); // here checks if the key if it was shift or any other extended keys if not clears the msb 
    shift &= ~(shiftcode[data] | E0ESC); // removes its modifier bit and clear the extended key flag
    return 0;
  } else if(shift & E0ESC){ // checks if the e0esc bit is currently set in shift
    // Last character was an E0 escape; or with 0x80
    data |= 0x80; // this sets the msb which differentiates extended keys from normal keys
    shift &= ~E0ESC; // this clears the e-0sc bit from the shift mask 
  }

  shift |= shiftcode[data];
  shift ^= togglecode[data];
  c = charcode[shift & (CTL | SHIFT)][data]; // this first checks which keymap to selet and then pick the corresponding charcter fto the keycode
  if(shift & CAPSLOCK){
    if('a' <= c && c <= 'z')
      c += 'A' - 'a';
    else if('A' <= c && c <= 'Z')
      c += 'a' - 'A';
  }
  return c;
}

void
kbdintr(void)
{
  consoleintr(kbdgetc);
}
