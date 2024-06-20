void setup()
{
      asm(".equ DDRB,0x04\n "
          ".equ DDRD , 0x0A\n"
          ".equ PORTB, 0x05\n"
          ".equ PIND ,0x09\n"
          "ldi r18,0\n"
          "out PIND,r18\n");
}

void loop()
{
  //in a loop go over all the leds and blink hem with a delay.
  //Do this until you are out of pin range
  asm("start: \n"
     "in r0,DDRB\n"
     "innerloop:"
     "breq r1,14 outofrange\n"
     "
     "outofrange:\n");
}