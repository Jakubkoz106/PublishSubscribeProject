#include <Arduino.h>
#line 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
#include "alp.h"

#line 3 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char allSpecies();
#line 8 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char allMeasurements();
#line 13 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char lizard();
#line 18 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char turtle();
#line 23 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char snake();
#line 28 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char mouse();
#line 33 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char spider();
#line 38 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char tempreature();
#line 43 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char humidity();
#line 48 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char light();
#line 53 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char oxygenation();
#line 58 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char carbonDioxide();
#line 30 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\main_server.ino"
void setup();
#line 43 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\main_server.ino"
void sendMeasure(char* message_to_send);
#line 49 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\main_server.ino"
void loop();
#line 3 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.c"
unsigned char allSpecies()
{
    return 0b11111111;
}

unsigned char allMeasurements()
{
    return 0b11111111;
}

unsigned char lizard()
{
    return 0b00000001;
}

unsigned char turtle()
{
    return 0b00000010;
}

unsigned char snake()
{
    return 0b00000011;
}

unsigned char mouse()
{
    return 0b00000100;
}

unsigned char spider()
{
    return 0b00000101;
}

unsigned char tempreature()
{
    return 0b00000001;
}

unsigned char humidity()
{
    return 0b000000010;
}

unsigned char light()
{
    return 0b00000011;
}

unsigned char oxygenation()
{
    return 0b00000100;
}

unsigned char carbonDioxide()
{
    return 0b00000101;
}

// const char* getSpeciesString(const unsigned char species)
// {
//     switch (species)
//     {
//     case lizard():
//         return "Lizard";
//         break;
//     case turtle():
//         return "Turtle";
//         break;
//     case snake():
//         return "Snake";
//         break;
//     case mouse():
//         return "Mouse";
//         break;
//     case spider():
//         return "Spider";
//         break;
//     default:
//         return NULL;
//         break;
//     }
// }

// const char* getSensorString(const unsigned char sensor)
// {
//     switch (sensor)
//     {
//     case tempreature():
//         return "Temperature";
//         break;
//     case humidity():
//         return "Humidity";
//         break;
//     case light():
//         return "Light";
//         break;
//     case oxygenation():
//         return "Oxygenation";
//         break;
//     case carbonDioxide():
//         return "Carbon Dioxide";
//         break;
//     default:
//         return NULL;
//         break;
//     }
// }
#line 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\main_server.ino"
#include <ZsutEthernet.h> 
#include <ZsutEthernetUdp.h>
#include <ZsutFeatures.h>
#include <stdio.h>
#include "alpmessagetype.h"
#include "alp.h"

#define MAX_BUFF 64

#define BROKER_PORT 1111

//#define MY_PUBLISHER_PORT 1111
#define MY_PUBLISHER_PORT 2222

byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
ZsutEthernetUDP Udp;
ZsutIPAddress address_ip=ZsutIPAddress(192,168,181,5);

//enum stateEnum {HELLO, WAITING, WORKING};
//int state;

unsigned char animal = snake();

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
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", 0b11000000 ,animal, tempreature(), outputTemperature & 0xFF, outputTemperature >> 8);
            sendMeasure(message_to_send);

        }else if(outputHumidity != ZsutAnalog1Read()){
            outputHumidity = ZsutAnalog1Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", 0b11000000, animal,humidity(), outputHumidity & 0xFF, outputHumidity >> 8);
            sendMeasure(message_to_send);

        }else if(outputLight != ZsutAnalog2Read()){
            outputLight = ZsutAnalog2Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", 0b11000000, animal,light(), outputLight & 0xFF, outputLight >> 8);
            sendMeasure(message_to_send);

        }else if(outputOxygenation != ZsutAnalog3Read()){
            outputOxygenation = ZsutAnalog3Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", 0b11000000, animal,oxygenation(), outputOxygenation & 0xFF, outputOxygenation >> 8);
            sendMeasure(message_to_send);

        }else if(outputCarbonDioxide != ZsutAnalog4Read()){
            outputCarbonDioxide = ZsutAnalog4Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c", 0b11000000, animal,carbonDioxide(), outputCarbonDioxide & 0xFF, outputCarbonDioxide >> 8);
            sendMeasure(message_to_send);
        }

}
