/*
* File: final_project.c
* Author: Sadia Khan
* Updated with proper delays and configurations for Proteus.
*/
#pragma config FOSC = INTRCIO // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF // Brown-out Reset Selection bits (BOR disabled) #pragma config IESO = OFF // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#include <xc.h>
#define _XTAL_FREQ 4000000 // Internal Oscillator at 4 MHz

// LCD control pins connected to PORTB

#define RS PORTBbits.RB4
#define RW PORTBbits.RC7
#define EN PORTBbits.RB5

// Keypad column and row connections to PORTC

#define C1 PORTCbits.RC0
#define C2 PORTCbits.RC1
#define C3 PORTCbits.RC2

#define A PORTCbits.RC3
#define B PORTCbits.RC4
#define C PORTCbits.RC5
#define D PORTCbits.RC6

// LEDs connected to PORTA

#define Red_LED PORTAbits.RA5

// Motor control pins connected to PORTB

#define RotateR PORTBbits.RB6
#define RotateL PORTBbits.RB7

unsigned char gpass[] = "1470"; // Predefined password
unsigned char pass[4]; // Password input array


// Send a nibble (4 bits) to the LCD
void lcd_nibble(unsigned char nibble)
{
    PORTAbits.RA0 = (nibble & 0x01);
    PORTAbits.RA1 = (nibble & 0x02) >> 1;
    PORTAbits.RA2 = (nibble & 0x04) >> 2;
    PORTAbits.RA4 = (nibble & 0x08) >> 3; // Fixed typo: changed from 'nibb' to 'nibble'

    EN = 1; // Enable signal
    __delay_ms(1);
    EN = 0; // Disable signal
}

// Send data to the LCD in 4-bit mode
void lcd_data(unsigned char data)
{
    RS = 1; // Select data register
      lcd_nibble(data >> 4); // Send higher nibble
      __delay_ms(2);
      lcd_nibble(data); // Send lower nibble
     __delay_ms(2);
}
// Send command to the LCD in 4-bit mode
void lcd_cmd(unsigned char cmd)
{
    RS = 0; // Select command register
    lcd_nibble(cmd >> 4); // Send higher nibble
    __delay_ms(2);
    lcd_nibble(cmd); // Send lower nibble
     __delay_ms(2);
}
// Initialize the LCD in 4-bit mode
void lcd_init()
{
//__delay_ms(20); // Wait for LCD to power up
lcd_nibble(0x03); // Initialize sequence
__delay_ms(5);
lcd_nibble(0x03);
__delay_ms(1);
lcd_nibble(0x03);
lcd_nibble(0x02); // 4-bit mode
lcd_cmd(0x28); // Function set: 2 lines, 5x8 matrix
lcd_cmd(0x06); // Entry mode: auto-increment
lcd_cmd(0x0C); // Display ON, cursor OFF
lcd_cmd(0x01); // Clear display
__delay_ms(2);
}

// Function to read the keypad input
void keypad()
{
   int x = 0;
   while (x < 4)
{
       TRISC = 0xF8; // Lower nibble output (columns), upper nibble input (rows)
// Column 1
   C1 = 1;
   C2 = 0;
   C3 = 0;
   if (A == 1)
{
    pass[x] = '1';
    lcd_data('1');
    while (A == 1);
     __delay_ms(500);
      x++;
}
if (B == 1)
{
    pass[x] = '4';
   lcd_data('4');
   while (B == 1);
    __delay_ms(500);
   x++;
}
if (C == 1)
{
   pass[x] = '7';
   lcd_data('7');
   while (C == 1);
    __delay_ms(500);
   x++;
}
if (D == 1)
{
    pass[x] = '*';
     lcd_data('*');
     while (D == 1);
     __delay_ms(500);
     x++;
}
// Column 2
C1 = 0;
C2 = 1;
C3 = 0;
if (A == 1)
{
   pass[x] = '2';
    lcd_data('2');
    while (A == 1);
   __delay_ms(500);
    x++;
}
if (B == 1)
{
       pass[x] = '5';
     lcd_data('5');
       while (B == 1);
       __delay_ms(200);
       x++;
}
if (C == 1)
{
     pass[x] = '8';
    lcd_data('8');
    while (C == 1);
   __delay_ms(500);
    x++;
}
if (D == 1)
{
    pass[x] = '0';
   lcd_data('0');
   while (D == 1);
 __delay_ms(500);
   x++;
}
// Column 3
C1 = 0;
C2 = 0;
C3 = 1;
if (A == 1)
{
    pass[x] = '3';
    lcd_data('3');
     while (A == 1);
     __delay_ms(500);
     x++;
}
if (B == 1)
{
    pass[x] = '6';
   lcd_data('6');
   while (B == 1);
   __delay_ms(500);
    x++;
}
if (C == 1)
{
     pass[x] = '9';
    lcd_data('9');
    while (C == 1);
  __delay_ms(500);
     x++;
}
if (D == 1)
{
  pass[x] = '#';
  lcd_data('#');
    while (D == 1);
    __delay_ms(500);
     x++;
     }
  }
}
// Function to display a string on the LCD
void lcd_str(const unsigned char *str, unsigned char L)
{
for (unsigned char i = 0; i < L; i++)
lcd_data(str[i]);
}
// Motor control functions
void motor_rotate_left() {
    RotateL = 1;
    RotateR = 0; // Make sure RotateR is off
    __delay_ms(1000); // Rotate motor for 1 second
    RotateL = 0; // Stop motor
}

void motor_rotate_right() {
    RotateL = 0; // Make sure RotateL is off
    RotateR = 1;
    __delay_ms(1000); // Rotate motor for 1 second
    RotateR = 0; // Stop motor
}
void main(void)
{
    ANSEL = 0x00;
    ANSELH = 0x00;
   
    PORTA = 0x00;
    PORTB = 0x00;
   
    TRISA = 0x00; // PORTA as output (LCD)
    TRISB = 0x00; // PORTB as output (LCD control and motor)
    TRISC = 0x00; // Upper nibble input (keypad rows), lower nibble output (keypad columns)
   
    // Initialize the LCD
    lcd_init();
    lcd_cmd(0x80); // Move to the first line
    lcd_str("Enter Password:", 16); // Display prompt
    lcd_cmd(0xC0); // Move to the second line

    while (1)
    {
        // Get the password input from the keypad
        keypad();

        // Check if the entered password matches the predefined password
        if (pass[0] == gpass[0] && pass[1] == gpass[1] && pass[2] == gpass[2] && pass[3] == gpass[3])
        {
            lcd_cmd(0x01); // Clear the LCD
            lcd_str("Correct Pass!", 14); // Display success message
            __delay_ms(400); // Give some time to display the message
            Red_LED = 0; // Turn off Red LED
            motor_rotate_left(); // Rotate motor left
            __delay_ms(5000);
            motor_rotate_right(); // Rotate motor right
        }
        else
        {
            lcd_cmd(0x01); // Clear the LCD
            lcd_str("Wrong Pass!", 12); // Display error message
            __delay_ms(400); // Give some time to display the message
            Red_LED = 1; // Turn on the Red LED to indicate wrong pass
           motor_rotate_right();
        }
       
        // Reset and prompt password entry again
        lcd_cmd(0x01); // Clear the display
        lcd_cmd(0x80); // Move to the first line
        lcd_str("Enter Password:", 16);
        lcd_cmd(0xC0); // Move to the second line
    }
}
