#ifndef ONEWIRETEMPERATURE_H
#define ONEWIRETEMPERATURE_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  // Pin numérique connectée aux sondes OneWire

class OneWireTemperature {
public:
    OneWireTemperature() : oneWire(ONE_WIRE_BUS), sensors(&oneWire) {}

    void begin() {
        sensors.begin();
        
        int deviceCount = sensors.getDeviceCount();
        Serial.print("Nombre de sondes détectées : ");
        Serial.println(deviceCount);
        
        if (deviceCount < 2) {
            Serial.println("⚠️ Moins de 2 sondes détectées !");
        }

        // Récupérer les adresses des deux sondes
        if (!sensors.getAddress(leftSensor, 0)) {
            Serial.println("⚠️ Impossible de récupérer l'adresse du capteur gauche.");
        }
        if (!sensors.getAddress(rightSensor, 1)) {
            Serial.println("⚠️ Impossible de récupérer l'adresse du capteur droit.");
        }

        Serial.print("Capteur gauche : "); printAddress(leftSensor);
        Serial.print("Capteur droit : "); printAddress(rightSensor);
    }

    float readTemperatureLeft() {
        return readTemperature(leftSensor);
    }

    float readTemperatureRight() {
        return readTemperature(rightSensor);
    }

private:
    OneWire oneWire;             
    DallasTemperature sensors;   
    DeviceAddress leftSensor, rightSensor;  

    float readTemperature(DeviceAddress deviceAddress) {
        sensors.requestTemperaturesByAddress(deviceAddress);
        float temperature = sensors.getTempC(deviceAddress);
        
        if (temperature == DEVICE_DISCONNECTED_C) {
            Serial.println("⚠️ Erreur : Capteur déconnecté !");
            return -999.0;
        }

        return temperature;
    }

    void printAddress(DeviceAddress deviceAddress) {
        for (uint8_t i = 0; i < 8; i++) {
            if (deviceAddress[i] < 16) Serial.print("0");
            Serial.print(deviceAddress[i], HEX);
        }
        Serial.println();
    }
};

#endif
