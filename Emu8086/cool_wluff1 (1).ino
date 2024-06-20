void setup()
{
asm(".equ DDRD,0x0A\n" // Data Direction Register for PORT D
".equ DDRB,0x04\n" // Data Direction Register for PORT B
".equ PORTD,0x0B\n" // PORT D
".equ PORTB, 0x05\n" // PORT B
".equ SPL, 0x3D\n" // Stack Pointer Low
".equ SPH, 0x3E\n" // Stack Pointer High
"ldi r16,0xFF\n"
"out SPL,r16\n"
"ldi r16,7\n"
"out SPH,r16\n"

"ldi r16,0b001111\n" // Set DDRB for output (assuming some other usage for PORT B)
"out DDRB,r16\n"
"ldi r16,0b11111111\n" // Set DDRD for output (8 LEDs connected to PORTD)
"out DDRD,r16\n"

"while_loop:"
"ldi r17,0x00\n" // Initialize counter to 0
"ldi r19,0x00\n" // Initialize counter to 0 
"output_loop:"
"out PORTD, r17\n" // Output the value of r20 to PORTD
"out PORTB,r19\n"
"cpi r17,10\n"
"brne skip \n"
"inc r19\n"
"ldi r17,0x00\n"
"rjmp output_loop\n"
"skip:\n"
"inc r17\n" // Increment r20
"rcall delay1s\n" // Call delay subroutine
"rjmp output_loop\n" // Repeat the loop

"delay1s:\n"
"ldi r18,50\n"
"main_while:\n"
"ldi r24,0x3E\n"
"ldi r25,0x9C\n"
"delay_loop:\n"
"sbiw r24,1\n"
"brne delay_loop\n"
"nop\n"
"dec r18\n"
"brne main_while\n"
"ret\n"
);
}

void loop()
{
}