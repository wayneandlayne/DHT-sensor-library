/* DHT library 

MIT license
written by Adafruit Industries
Modified by Matthew Beckler and Adam Wolf of Wayne and Layne, LLC to work better in a data logging context.
*/

#include "DHT.h"

DHT::DHT(uint8_t pin, uint8_t type) {
  _pin = pin;
  _type = type;
}

void DHT::begin(void) {
  // set up the pins!
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}

//boolean S == Scale.  True == Farenheit; False == Celcius
// Be sure to call read() before calling this function!
float DHT::readTemperature(bool S) {
  float f;

  switch (_type) {
    case DHT11:
      f = data[2];
      if (S)
      	f = convertCtoF(f);
      return f;

    case DHT22:
    case DHT21:
    default:
      f = data[2] & 0x7F;
      f *= 256;
      f += data[3];
      f /= 10;
      if (data[2] & 0x80)
	f *= -1;
      if (S)
	f = convertCtoF(f);
      return f;
  }
}

float DHT::convertCtoF(float c) {
	return c * 9 / 5 + 32;
}

// Be sure to call read() before calling this function!
float DHT::readHumidity(void) {
  float f;
  switch (_type) {
    case DHT11:
      f = data[0];
      return f;
    case DHT22:
    case DHT21:
    default:
      f = data[0];
      f *= 256;
      f += data[1];
      f /= 10;
      return f;
  }
}

// Call this when you wake from sleep to fetch the latest reading
// Return value: True = success, False = failure
bool DHT::read(void) {
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;

  // pull the pin high and wait 250 milliseconds
  digitalWrite(_pin, HIGH);
  delay(250);

  // Wayne and Layne removed code here to ensure that we only sample every two seconds
  // since that is handled by the datalogging code

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // now pull it low for ~20 milliseconds
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(20);
  cli();
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);

  // read in timings
  for ( i=0; i< MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(_pin) == laststate) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    laststate = digitalRead(_pin);

    if (counter == 255) {
        break;
    }

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      data[j/8] <<= 1;
      if (counter > 6) {
        data[j/8] |= 1;
      }
      j++;
    }

  }

  sei();
  
  /*
  Serial.println(j, DEC);
  Serial.print(data[0], HEX); Serial.print(", ");
  Serial.print(data[1], HEX); Serial.print(", ");
  Serial.print(data[2], HEX); Serial.print(", ");
  Serial.print(data[3], HEX); Serial.print(", ");
  Serial.print(data[4], HEX); Serial.print(" =? ");
  Serial.println(data[0] + data[1] + data[2] + data[3], HEX);
  */

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  

  return false;

}
