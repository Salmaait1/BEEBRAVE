// Fichier : LoRaWAN.h
#ifndef LORAWAN_H
#define LORAWAN_H
#include <MKRWAN.h>

class LoRaWAN {
public:
    bool begin(String appEUI, String appKey) {
        if (!modem.begin(EU868)) return false;
        return modem.joinOTAA(appEUI, appKey);
    }
    void send(byte *payload, size_t length) {
        modem.beginPacket();
        modem.write(payload, length);
        modem.endPacket();
    }
private:
    LoRaModem modem;
};
#endif
