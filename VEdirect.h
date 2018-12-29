// Victron VE.direct MPPT solar charger
// ---------------------------------
//
// By B.Swildens (bas@thingshub.nl)
// December 2018
//
// Documentation:
//		- The Victron VE.direct datasheet
//

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SoftwareSerial.h>


class VEdirect {
	public:
		VEdirect(void);
		void begin(uint8_t pin_rx, uint8_t pin_tx);
		int read(float *v, float *i);
	private:
		uint8_t _pin_rx, _pin_tx;
		Stream *vedirect_data;		
};
