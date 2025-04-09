// Fichier : DHT11.h
#ifndef DHT11_H
#define DHT11_H
#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT22

class DHT11Sensor {
public:
    DHT11Sensor() : dht(DHTPIN, DHTTYPE) {}
    void begin() { dht.begin(); }
    void read(float &temperature, float &humidity) {
        temperature = dht.readTemperature();
        humidity = dht.readHumidity();
    }
private:
    DHT dht;
};
#endif