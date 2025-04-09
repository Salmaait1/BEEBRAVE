#include "DHT11.h"
#include "DHT22.h"
#include "VEML7700.h"
#include "HX711Sensor.h"
#include "LoRaWAN.h"
#include "OneWireTemperature.h"
#include "ArduinoLowPower.h"

// Définition de la broche et des seuils batterie
#define ANALOG_PIN A1  
#define V_BAT_MAX 3.3   
#define V_BAT_MIN 0.0   

// REGULATEUR 
#define SHDN_PIN 4  // Broche de contrôle du régulateur (Shutdown)

// Communication UART
#define SERIAL_BAUDRATE 115200
#define RX_PIN 13  // D13 - RX
#define TX_PIN 14  // D14 - TX

DHT11Sensor dht11; // CT LE BLEU 
DHT22Sensor dht22;
VEML7700Sensor veml7700;
HX711Sensor hx711;
LoRaWAN lorawan;
OneWireTemperature oneWireTemp;  

String appEUI = "0000000000000000";
String appKey = "70C141C1E9629690E70ACF0077435A69";

float coeffLeft = 1.01;
float coeffRight = 1.01;

union FloatUnion {
    float value;
    byte bytes[4];
};

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
    //while (!Serial);
    Serial.println("Début !!");
    pinMode(SHDN_PIN, OUTPUT);
    digitalWrite(SHDN_PIN, LOW);  // Désactiver les capteurs au démarrage
    dht11.begin();
    dht22.begin();
    veml7700.begin();
    oneWireTemp.begin();  
    hx711.begin();
    Serial.println("Fin !!");

    if (!lorawan.begin(appEUI, appKey)) {
        Serial.println("Erreur de connexion LoRaWAN !");
        while (1);
    }
    Serial1.begin(115200);
    //while (!Serial);
    Serial.println("Début SR");
    Serial.println("Lorawan OK");
}

void loop() {
    // Activer le régulateur 
    digitalWrite(SHDN_PIN, HIGH);

    // Lire les données des capteurs
    Serial.println("DEBUT LECTURE");
    float temperature, humidity;
    dht11.read(temperature, humidity);  
    Serial.println("OK DHT11");
    float temperatureDHT22, humidityDHT22;
    dht22.read(temperatureDHT22, humidityDHT22);  
    Serial.println("OK DHT22");
    float lux = veml7700.read();  
    Serial.println("OK VEML");
    float poids =  hx711.read();  
    Serial.println("OK HX711");
    float oneWireTempLeft = oneWireTemp.readTemperatureLeft();  
    float oneWireTempRight = oneWireTemp.readTemperatureRight();  

    // Lecture de la tension batterie
    int valeurAnalogique = analogRead(ANALOG_PIN);
    Serial.println(valeurAnalogique);
    float tension = (valeurAnalogique * 4.2) / 1023.0;
    //int pourcentageBatterie = map(tension * 100, V_BAT_MIN * 100, V_BAT_MAX * 100, 0, 100);
    //pourcentageBatterie = constrain(pourcentageBatterie, 0, 100);

    // Affichage des valeurs lues
    Serial.print("Température DHT11: "); Serial.print(temperature);
    Serial.print(" °C | Humidité: "); Serial.print(humidity);
    Serial.print("Température DHT22: "); Serial.print(temperatureDHT22);
    Serial.print(" °C | Humidité: "); Serial.print(humidityDHT22);
    Serial.print(" % | Luminosité: "); Serial.print(lux);
    Serial.print(" lux | Température OneWire Gauche: "); Serial.print(oneWireTempLeft);
    Serial.print(" °C | Température OneWire Droite: "); Serial.print(oneWireTempRight);
    Serial.print(" °C | Poids: "); Serial.print(poids);
    Serial.print(" kg | Batterie: "); Serial.print(tension);
    Serial.println(" V");

    // Lecture des données reçues de la Nano 33 BLE Sense
        float queenPresence = 0;
        if (Serial1.available()) {
            String receivedData = Serial1.readStringUntil('\n');
            queenPresence = receivedData.toFloat();
            Serial.println("Microphone Data (Queen Presence): " + String(queenPresence));
        }

    // Création du payload (36 octets)
    byte payload[40];  

    // Convertir chaque valeur float en 4 octets
    FloatUnion tempUnion, humUnion, tempDHT22Union, humDHT22Union;
    FloatUnion luxUnion, oneWireLeftUnion, oneWireRightUnion, weightUnion, batteryUnion, queenPresenceUnion;
    
    tempUnion.value =  temperature;
    humUnion.value = humidity;
    tempDHT22Union.value = temperatureDHT22;
    humDHT22Union.value = humidityDHT22;
    luxUnion.value = lux;
    oneWireLeftUnion.value = oneWireTempLeft;
    oneWireRightUnion.value = oneWireTempRight;
    weightUnion.value = poids;
    batteryUnion.value = tension;
    queenPresenceUnion.value = queenPresence;

    // Mettre les octets dans le payload
    for (int i = 0; i < 4; i++) {
        payload[i] = tempUnion.bytes[i];  
        payload[i + 4] = humUnion.bytes[i];  
        payload[i + 8] = tempDHT22Union.bytes[i];  
        payload[i + 12] = humDHT22Union.bytes[i];  
        payload[i + 16] = luxUnion.bytes[i];  
        payload[i + 20] = oneWireLeftUnion.bytes[i];  
        payload[i + 24] = oneWireRightUnion.bytes[i];  
        payload[i + 28] = weightUnion.bytes[i];  
        payload[i + 32] = batteryUnion.bytes[i]; 
        payload[i + 36] = queenPresenceUnion.bytes[i];  
    }

    // Envoi des données via LoRaWAN
    lorawan.send(payload, sizeof(payload));
    //Serial.println("📡 Données envoyées !");
    // Désactiver le module LoRaWAN pour économiser de l'énergie
    lorawan.sleep();  // Désactive LoRaWAN après l'envoi des données

    // Désactiver le régulateur
    digitalWrite(SHDN_PIN, LOW);
    // Passer en mode deep sleep
    LowPower.deepSleep(600000); // 10 MINUTES
    
}