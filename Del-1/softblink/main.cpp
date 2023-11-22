/*
 * softblink.cpp
 *
 * Created: 25.10.2023 11:28:25
 * Author : Truls Kolstad
 */ 

#include <avr/io.h>
#include <util/delay.h>

// Definerer pin som LED er koplet til
#define ledPin PD6
// Tid for delay til � styre dimmeperioden, brukes i funksjon som tar inn double.
// �k for tregere blinking, mink for raskere blink.
const double delayTime = 10;

void pwmInit() {
	// Konfigurer PD6/OC0A som en utgang.
	DDRD |= (1 << ledPin);

	// Konfigurer Timer/Counter Control Register 0A til
	// Fast PWM mode med ikke-invertert utgang.
	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
	
	// Ingen prescaler, full fart @ 3.9kHz
	TCCR0B = (1 << CS00); 
	
	// Startverdi sendt til OCR0A komparator
	OCR0A = 128;  
}

int main(void) {
	// Initsialiserer pwm p� mikrokontrolleren
	pwmInit();

	while (1) {
		// L�kke som stegvis �ker lysstyrken.
		// Tid mellom hver �kning styres av delay funksjonen.
		for (int brightness = 0; brightness <= 255; brightness++) {
			OCR0A = brightness;
			_delay_ms(delayTime); 
		}
		
		// L�kke som stegvis minker lysstyrken
		for (int brightness = 255; brightness >= 0; brightness--) {
			OCR0A = brightness;
			_delay_ms(delayTime); 
		}
	}

	return 0;
}