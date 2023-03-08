#include <ZsutEthernet.h> 
#include <ZsutEthernetUdp.h>
#include <ZsutFeatures.h>
#include <stdio.h>
#include "alp_message_type.h"
#include "alp.h"

#define MAX_BUFF 64

#define BROKER_PORT 1111

#define MY_PUBLISHER_PORT 1111
//#define MY_PUBLISHER_PORT 2222
//#define MY_PUBLISHER_PORT 3333
//#define MY_PUBLISHER_PORT 4444
//#define MY_PUBLISHER_PORT 5555

byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x04};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x05};

ZsutEthernetUDP Udp;
ZsutIPAddress address_ip=ZsutIPAddress(192,168,181,5);

//SET ANIMAL
unsigned char animal = LIZARD;
//unsigned char animal = TURTLE;
//unsigned char animal = SNAKE;
//unsigned char animal = MOUSE;
//unsigned char animal = SPIDER;

uint16_t outputTemperature=0;
uint16_t outputHumidity=0;
uint16_t outputLight=0;
uint16_t outputOxygenation=0;
uint16_t outputCarbonDioxide=0;

void setup()
{
    Serial.begin(115200);
    ZsutEthernet.begin(mac); 
    unsigned int localPort = MY_PUBLISHER_PORT;
    Udp.begin(localPort);

}

//unsigned long period_time = 5000;
//unsigned long current_time = 0;
//unsigned long saved_time = 0;

void sendMeasure(char* message_to_send){
    Udp.beginPacket(address_ip, BROKER_PORT);
    int s=Udp.write(message_to_send, strlen(message_to_send));
    Udp.endPacket();
}

void loop(){
        char message_to_send[MAX_BUFF];
        if(outputTemperature != ZsutAnalog0Read()){
            outputTemperature = ZsutAnalog0Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c",  PUBLISHER, animal, TEMPREATURE, outputTemperature & 0xFF, outputTemperature >> 8);
            sendMeasure(message_to_send);

        }else if(outputHumidity != ZsutAnalog1Read()){
            outputHumidity = ZsutAnalog1Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", PUBLISHER, animal, HUMIIDITY, outputHumidity & 0xFF, outputHumidity >> 8);
            sendMeasure(message_to_send);

        }else if(outputLight != ZsutAnalog2Read()){
            outputLight = ZsutAnalog2Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", PUBLISHER, animal, LIGHT, outputLight & 0xFF, outputLight >> 8);
            sendMeasure(message_to_send);

        }else if(outputOxygenation != ZsutAnalog3Read()){
            outputOxygenation = ZsutAnalog3Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", PUBLISHER, animal, OXYGENATION, outputOxygenation & 0xFF, outputOxygenation >> 8);
            sendMeasure(message_to_send);

        }else if(outputCarbonDioxide != ZsutAnalog4Read()){
            outputCarbonDioxide = ZsutAnalog4Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", PUBLISHER, animal, CARBONDIOXIDE, outputCarbonDioxide & 0xFF, outputCarbonDioxide >> 8);
            sendMeasure(message_to_send);
        }

}