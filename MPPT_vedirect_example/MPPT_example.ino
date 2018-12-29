// VE.direct MPPT example
// -----------------------------
//
// By B. Swildens (bas@thingshub.nl)
// December 2018

#include <VEdirect.h>

float v,i;
int error;

VEdirect my_MPPT;

void setup() {
	my_MPPT.begin(D1,D2);
	Serial.begin(9600);
}

void loop() {
	error = my_MPPT.read(&v,&i);
	if (! error) {
		Serial.println("Voltage: "+String(v));
		Serial.println("Currect: "+String(i));
	}
	delay(100);
}
