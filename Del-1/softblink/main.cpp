/*
 * softblink.cpp
 *
 * Created: 25.10.2023 11:28:25
 * Author : hakka
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PD6

void init_PWM() {
	// Set PD6 (OC0A) as an output
	DDRD |= (1 << LED_PIN);

	// Set the Timer/Counter 0 to Fast PWM mode with non-inverted output
	TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
	TCCR0B = (1 << CS00);  // No prescaler, running at full speed

	// Set the initial PWM duty cycle (brightness)
	OCR0A = 128;  // Adjust this value for desired brightness
}

int main(void) {
	init_PWM();

	while (1) {
		// Soft blink by changing the PWM duty cycle
		for (int brightness = 0; brightness <= 255; brightness++) {
			OCR0A = brightness;
			_delay_ms(10);  // Adjust this delay for the soft blink speed
		}

		for (int brightness = 255; brightness >= 0; brightness--) {
			OCR0A = brightness;
			_delay_ms(10);  // Adjust this delay for the soft blink speed
		}
	}

	return 0;
}