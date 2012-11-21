#ifndef DHT_H
#define DHT_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/* DHT library 

MIT license
written by Adafruit Industries
Modified by Matthew Beckler and Adam Wolf of Wayne and Layne, LLC to work better in a data logging context.
*/

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

class DHT {
 private:
  uint8_t data[6];
  uint8_t _pin, _type;

 public:
  DHT(uint8_t pin, uint8_t type);
  void begin(void);
  bool read(void);
  float readTemperature(bool S=false);
  float convertCtoF(float);
  float readHumidity(void);

};
#endif

