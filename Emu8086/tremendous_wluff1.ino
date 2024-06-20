void setup()
{
  asm(
      ".equ DDRD,0x0A\n"
      ".equ PORTD,0x0B\n"
      ".equ SPH,0x3E\n"
      ".equ SPL,0x3D\n"
      "ldi r16,0xFF\n"
      "out SPL,r16\n"
      "ldi r16,7\n"
      "out SPH,r16\n" 
      // DON'T USE R18,R24,R25
      "ldi r16,0b01111111\n"
      "out DDRD, r16\n"
      // SET X POINTER REGISTER ADDRESS TO 0x200
      "ldi r26, 0x00\n" // r26 is the low byte of the X pointer
      "ldi r27, 0x02\n" // r27 is the high byte of the X pointer
      // STORE CORRECT VALUES AT X POINTER ADDRESS
      "ldi r16, 0b00111111\n" // value for 0
      "st X+, r16\n"
      "ldi r16, 0b00000110\n" // value for 1
      "st X+, r16\n"
      "ldi r16, 0b01011011\n" // value for 2
      "st X+, r16\n"
      "ldi r16, 0b01001111\n" // value for 3
      "st X+, r16\n"
      "ldi r16, 0b01100110\n" // value for 4
      "st X+, r16\n"
      "ldi r16, 0b01101101\n" // value for 5
      "st X+, r16\n"
      "ldi r16, 0b01111101\n" // value for 6
      "st X+, r16\n"
      "ldi r16, 0b00000111\n" // value for 7
      "st X+, r16\n"
      "ldi r16, 0b01111111\n" // value for 8
      "st X+, r16\n"
      "ldi r16, 0b01101111\n" // value for 9
      "st X+, r16\n"
      // RESET X POINTER REGISTER ADDRESS TO 0x200
      "ldi r26, 0x00\n" // r26 is the low byte of the X pointer
      "ldi r27, 0x02\n" // r27 is the high byte of the X pointer
      // DISPLAY VALUES EVERY SECOND 
      // (RCALL delay1s = delays hardware for 1 second),
      "main_loop:\n"
      "ld r16, X+\n" // load value from X pointer
      "out PORTD, r16\n" // output to PORTD
      "rcall delay1s\n" // delay for 1 second
      "cpi r26, 10\n" // check if we've displayed all digits
      "brne main_loop\n" // if not, continue main loop
      // RESET X POINTER REGISTER ADDRESS TO 0x200
      "ldi r26, 0x00\n" // reset X pointer low byte
      "ldi r27, 0x02\n" // reset X pointer high byte
      "rjmp main_loop\n"
      // DELAY PROCEDURE
      "delay1s:\n"
      "ldi r18,100\n"
      "delay_loop:\n"
      "ldi r24,0x3E\n"
      "ldi r25,0x9C\n"
      "delay_inner_loop:\n"
      "sbiw r24,1\n"
      "brne delay_inner_loop\n"
      "nop\n"
      "dec r18\n"
      "brne delay_loop\n"
      "ret\n");
}

void loop()
{
  // Empty loop
}
