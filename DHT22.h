// Fichier : DHT11.h
#ifndef DHT22_H
#define DHT22_H
#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT22

class DHT22Sensor {
public:
    DHT22Sensor() : dht(DHTPIN, DHTTYPE) {}
    void begin() { dht.begin(); }
    void read(float &temperature, float &humidity) {
        temperature = dht.readTemperature();
        humidity = dht.readHumidity();
    }
private:
    DHT dht;
};
#endif