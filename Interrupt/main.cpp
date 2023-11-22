/*
 * Interrupt.cpp
 *
 * Created: 28.10.2023 10:32:58
 * Author : Andreas Ekeberg Syversen
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define buttonPin PD0   // Knappens inngangspinne (PD2)
#define ledPin PD6      // LED-utgangspinne (PD6)

volatile uint8_t ledState = 0;  // 0 = av (knapp er ikke trykket)

// Pin Change ISR-funksjon
ISR(PCINT2_vect) {

	// Sjekker om knappen er trykket
	if (!(PIND & (1 << buttonPin))) {
		// Bytt tilstanden til lysdioden
		ledState = !ledState;
		}
		PORTD &= ~(1 << ledPin);
	
}

int main(void) {
	DDRD &= ~(1 << buttonPin);  // Sett knappen (PD2) som inngang
	PORTD |= (1 << buttonPin);  // Aktiver pull-up motstand for knappen

	DDRD |= (1 << ledPin);  // Sett lysdioden (PD6) som utgang

	//pin change interrupts for PCINT18
	PCICR |= (1 << PCIE2);

	// Aktiver interrupts for den spesifikke pinnen (PD2)
	PCMSK2 |= (1 << PCINT16);

	// Aktiver globale interrupts
	sei();

	while (1) {
		if (ledState) {
			} else {
			PORTD &= ~(1 << ledPin);
	}
		}

	return 0;
}
