// Fichier : VEML7700.h
#ifndef VEML7700_H
#define VEML7700_H
#include <Wire.h>
#include "Adafruit_VEML7700.h"

class VEML7700Sensor {
public:
    bool begin() { return veml.begin(); }
    float read() { return veml.readLux(); }
private:
    Adafruit_VEML7700 veml;
}; 
#endif