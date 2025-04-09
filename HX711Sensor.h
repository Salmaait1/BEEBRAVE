// Fichier : HX711Sensor.h
#ifndef HX711SENSOR_H
#define HX711SENSOR_H
#include "HX711.h"
#define DT 7
#define SCK 6

class HX711Sensor {
public:
    HX711Sensor() {} // Constructeur

    void begin() {
        balance.begin(DT, SCK);
    }

    float read() {
        float poids = 0;
        for (int i = 0; i < 20; i++) {
            poids += balance.get_units();
            delay(50);
        }
        return ((poids / 20) / 19825.0 - 3.3);  // Appliquer le facteur d'échelle
    }

private:
    HX711 balance; // Déclaration de l'objet balance
};
#endif
