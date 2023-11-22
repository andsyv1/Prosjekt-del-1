/*
 * softblink.cpp
 *
 * Created: 25.10.2023 11:28:25
 * Author : Truls Kolstad
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6

void init_PWM() {
	// Set PD6/OC0A as an output pin. 
	DDRD |= (1 << LED_PIN);

	// Set the Timer/Counter Control Register 0 to Fast PWM mode with non-inverted output
	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
	
	// No prescaler, running at full speed
	TCCR0B = (1 << CS00); 
	
	// Set the initial PWM duty cycle (brightness)
	OCR0A = 128;  // Adjust this value for desired brightness
}

int main(void) {
	init_PWM();

	while (1) {
		// Soft blink by changing the PWM duty cycle
		for (int brightness = 0; brightness <= 255; brightness++) {
			OCR0A = brightness;
			_delay_ms(1);  // Adjust this delay for the soft blink speed
		}

		for (int brightness = 255; brightness >= 0; brightness--) {
			OCR0A = brightness;
			_delay_ms(1);  // Adjust this delay for the soft blink speed
		}
	}

	return 0;
}