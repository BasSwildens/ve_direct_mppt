# VE.direct  
  
Arduino library for Victron VE.direct MPPT solarcharger (https://www.victronenergy.nl/)  
This library uses SoftSerial to connect to the MPPT solarcharger.  
  
## Usage
  
* Define VE.direct object:  
VEdirect(uint8_t pin_rx, uint8_t pin_tx);  
i.e. VEdirect myMPPT(pinRX,pinTX);  
  
* Start object:  
void begin(void);  
i.e. myMPPT.begin();  
  
* Read values:  
int read(float *v, float *i);  
i.e. error = myMPPT(voltage,current);  
  
Reads the battery voltage and charge current values, return code is 0, if new values were read, and 1 if there were no new values.  
  
  
