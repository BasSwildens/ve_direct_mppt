// Victron VE.direct MPPT solar charger
// ---------------------------------
//
// By B.Swildens (bas@thingshub.nl)
// December 2018
//
// Documentation:
//		- The Victron VE.direct datasheet
//

#include "VEdirect.h"

VEdirect::VEdirect(void) {

}

// --------------------------------------------------------
// VEdirect:read
// --------------------------------------------------------
int VEdirect::read(float *v, float *i) {
	byte buffer;
	int value;
	int len = 0;
	int v_serial = 0;
	int i_serial = 0;
	int checksum_is;
	int checksum_ok = 0;
	int error = 1;
	while ((vedirect_data->available() > 0) && (vedirect_data->available() >= (10-len))) {
		buffer = vedirect_data->read();
		value = int(buffer);
		switch (len) {
			case (0): if (value != 170) { len = -1; }; break;
			case (1): if (value != 192) { len = -1; }; break;
			case (2): v_serial = value; checksum_is = value; break;
			case (3): v_serial += (value << 8); checksum_is += value; break;
			case (4): i_serial = value; checksum_is += value; break;
			case (5): i_serial += (value << 8); checksum_is += value; break;
			case (6): checksum_is += value; break;
			case (7): checksum_is += value; break;
			case (8): if (value == (checksum_is % 256)) { checksum_ok = 1; } else { len = -1; }; break;
			case (9): if (value != 171) { len = -1; }; break;
		}
		len++;
		if (len == 10 && checksum_ok == 1) {
			*v = (float)v_serial/10.0;
			*i = (float)i_serial/10.0;
			len = 0; checksum_ok = 0; v_serial = 0.0; i_serial = 0.0; checksum_is = 0;
			error = 0;
		}
		yield();
	}
	return error;
}

void VEdirect::begin(uint8_t pin_rx, uint8_t pin_tx) {
	_pin_rx = pin_rx;
	_pin_tx = pin_tx;

	SoftwareSerial *softSerial = new SoftwareSerial(_pin_rx, _pin_tx);

	//Initialize the 'Wire' class for I2C-bus communication.
	softSerial->begin(9600);

	vedirect_data = softSerial;
}

