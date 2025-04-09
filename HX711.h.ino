// Fichier : HX711Sensor.h
#ifndef HX711SENSOR_H
#define HX711SENSOR_H
#include "HX711.h"
#define DT 7
#define SCK 6

class HX711Sensor {
public:
    void begin() {
        balance.begin(DT, SCK);
        balance.tare();
    }
    float read() {
        float poids = 0;
        for (int i = 0; i < 20; i++) {
            poids += balance.get_units();
            delay(50);
        }
        return (poids / 20) / 19825.0;
    }
private:
    HX711 balance;
};
#endif