# This is an Arduino library for the DHT series of low cost temperature/humidity sensors. #

## IMPORTANT: You must rename this folder to be "DHT" instead of "DHT-sensor-library", otherwise it won't work with the Arduino software! ##

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder DHT. Check that the DHT folder contains DHT.cpp and DHT.h. Place the DHT library folder your <arduinosketchfolder>/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

Note: This library has been modified to work better in a sleep-based datalogging situation, by assuming that at least two seconds have passed since the last reading, avoid the need to use millis(). The millis() function may not even work correctly anyway when using advanced sleep modes.  Now, you need to manually call dht.read() when you wake up from sleep to get the latest data. Modified by Matthew Beckler and Adam Wolf of Wayne and Layne, LLC, as part of our Battery Booster Shield project - http://www.wayneandlayne.com/projects/battery-booster-shield/
