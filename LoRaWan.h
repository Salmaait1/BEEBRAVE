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

    void sleep() {
        //modem.sendAT("+CSCLK=1");  // Active le mode veille (vous pouvez ajuster la commande en fonction de vos besoins)
        modem.sleep();  // Passe le modem en mode veille
    }


private:
    LoRaModem modem;
};

#endif
