#include <ZsutEthernet.h> 
#include <ZsutEthernetUdp.h>
#include <ZsutFeatures.h>
#include <stdio.h>
#include "alp_message_type.h"
#include "alp.h"

#define MAX_BUFF 64
#define MAX_BUFF_RECIEVE 6

#define BROKER_PORT 1111
ZsutEthernetUDP Udp;
ZsutIPAddress address_ip=ZsutIPAddress(192,168,181,5);

//#define MY_PUBLISHER_PORT 1111
//#define MY_PUBLISHER_PORT 2222
#define MY_PUBLISHER_PORT 3333
//#define MY_PUBLISHER_PORT 4444
//#define MY_PUBLISHER_PORT 5555

//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x04};
//byte mac[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x05};


//SET ANIMAL
//unsigned char animal = LIZARD;
//unsigned char animal = TURTLE;
unsigned char animal = SNAKE;
//unsigned char animal = MOUSE;
//unsigned char animal = SPIDER;

//SUBSCIPTION
unsigned char mySubscription[] = {CLIENT_SUBSCRIBE, ALL_SPIECIES_MESSAGE, ALL_SENSORS_MESSAGE, END_MESSAGE, '\0'};

unsigned char myUnsubscription[] = {CLIENT_SUBSCRIBE, SNAKE, ALL_SENSORS_MESSAGE, END_MESSAGE, SPIDER, OXYGENATION, LIGHT, END_MESSAGE, '\0'};
unsigned char myAddsubscription[] = {CLIENT_SUBSCRIBE, SNAKE, ALL_SENSORS_MESSAGE, END_MESSAGE, SPIDER, OXYGENATION, LIGHT, END_MESSAGE, '\0'};

uint16_t outputTemperature=0;
uint16_t outputHumidity=0;
uint16_t outputLight=0;
uint16_t outputOxygenation=0;
uint16_t outputCarbonDioxide=0;

enum stateEnum {SUBSCRIBE, UNSUBSCRIBE, ADDSUBSRIPTION, WORKING};
int state;

unsigned long start_time;

//UNSUBSCRIBE
unsigned long time_to_send_unsubscribe = 30000;
bool send_unsubscribe = false;

//ADD SUBSCRIPTION
unsigned long time_to_send_addsubscribe = 30000;
bool send_add_subscription = false;

void setup()
{
    Serial.begin(115200);
    ZsutEthernet.begin(mac); 
    unsigned int localPort = MY_PUBLISHER_PORT;
    Udp.begin(localPort);

    start_time = ZsutMillis();

    //SEND SUBSCRIBE/UNSUBSCRIBE OR JUST START WORKING
    state = stateEnum::SUBSCRIBE; 
}

void sendMeasure(char* message_to_send){
    Udp.beginPacket(address_ip, BROKER_PORT);
    int s=Udp.write(message_to_send, strlen(message_to_send));
    Udp.endPacket();

    uint16_t value = (uint8_t)message_to_send[3] | message_to_send[4] << 8;

    Serial.print("SEND: Spieces: ");
    Serial.print(getSpeciesString(message_to_send[1]));

    Serial.print(" |  Sensor: ");
    Serial.print(getSensorString(message_to_send[2]));

    Serial.print(" |  Value: ");
    Serial.println(value);
    Serial.println();
}

void loop(){

    if (state == stateEnum::SUBSCRIBE)
    {
        unsigned char* subscribe_message_to_send = interpretSubscriptionMessage(mySubscription);

        Udp.beginPacket(address_ip, BROKER_PORT);
        int r=Udp.write(subscribe_message_to_send, MAX_BUFF);
        Udp.endPacket();
        Serial.println("Subscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::UNSUBSCRIBE)
    {
        unsigned char* unsubscribe_message_to_send = interpretSubscriptionMessage(myUnsubscription);

        Udp.beginPacket(address_ip, BROKER_PORT);
        int r=Udp.write(unsubscribe_message_to_send, MAX_BUFF);
        Udp.endPacket();
        Serial.println("Unsubscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::ADDSUBSRIPTION)
    {
        unsigned char* addsubscribe_message_to_send = interpretSubscriptionMessage(myAddsubscription);

        Udp.beginPacket(address_ip, BROKER_PORT);
        int r=Udp.write(addsubscribe_message_to_send, MAX_BUFF);
        Udp.endPacket();
        Serial.println("Add subscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::WORKING)
    {
        char message_to_send[MAX_BUFF];
        if(outputTemperature != ZsutAnalog0Read()){
            outputTemperature = ZsutAnalog0Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c%c",  PUBLISHER, animal, TEMPREATURE, outputTemperature & 0xFF, outputTemperature >> 8, END_MESSAGE);
            sendMeasure(message_to_send);

        }else if(outputHumidity != ZsutAnalog1Read()){
            outputHumidity = ZsutAnalog1Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c%c", PUBLISHER, animal, HUMIIDITY, outputHumidity & 0xFF, outputHumidity >> 8, END_MESSAGE);
            sendMeasure(message_to_send);

        }else if(outputLight != ZsutAnalog2Read()){
            outputLight = ZsutAnalog2Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c%c", PUBLISHER, animal, LIGHT, outputLight & 0xFF, outputLight >> 8, END_MESSAGE);
            sendMeasure(message_to_send);

        }else if(outputOxygenation != ZsutAnalog3Read()){
            outputOxygenation = ZsutAnalog3Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c%c", PUBLISHER, animal, OXYGENATION, outputOxygenation & 0xFF, outputOxygenation >> 8, END_MESSAGE);
            sendMeasure(message_to_send);

        }else if(outputCarbonDioxide != ZsutAnalog4Read()){
            outputCarbonDioxide = ZsutAnalog4Read();
            snprintf(message_to_send, MAX_BUFF, "%c%c%c%c%c%c", PUBLISHER, animal, CARBONDIOXIDE, outputCarbonDioxide & 0xFF, outputCarbonDioxide >> 8, END_MESSAGE);
            sendMeasure(message_to_send);
        }

        int packetSize=Udp.parsePacket();

        if(packetSize)
        { 
            unsigned char recived_message[MAX_BUFF_RECIEVE];
            memset(&recived_message[0], 0, sizeof(recived_message));
            
            int r=Udp.read(recived_message, sizeof(recived_message));

            if (recived_message[0] == PUBLISHER)
            {
                uint16_t recieved_value = (uint8_t)recived_message[3] | recived_message[4] << 8;
                Serial.print("RECIEVED: Spieces: ");
                Serial.print(getSpeciesString(recived_message[1]));

                Serial.print(" |  Sensor: ");
                Serial.print(getSensorString(recived_message[2]));

                Serial.print(" |  Value: ");
                Serial.println(recieved_value);
                Serial.println();
            }
        }

        if (ZsutMillis() - start_time >= time_to_send_unsubscribe && send_unsubscribe)
        {
            send_unsubscribe = false;
            state = stateEnum::UNSUBSCRIBE;
        }

        if (ZsutMillis() - start_time >= time_to_send_addsubscribe && send_add_subscription)
        {
            send_add_subscription = false;
            state = stateEnum::ADDSUBSRIPTION;
        }
    }
}

/**
 * @brief Function used for finding ALL_SPIECES_MESSAGE and ALL_SENSORS_MESSAGE, iterprete and build message. 
 * 
 * @param subscription subscription with ALL_SPIECES_MESSAGE and ALL_SENSORS_MESSAGE
 * @return unsigned* builded message
 */
unsigned char* interpretSubscriptionMessage(unsigned char subscription[])
{
    unsigned char* interpretedMessage = malloc(MAX_BUFF);
    unsigned char* sensorsList = allSensorsList();
    unsigned char* spiecesList = allSpeciesList();

    int temp = 0;

    for (int i = 0; i < strlen(subscription); i++)
    {

        if (subscription[i] == ALL_SENSORS_MESSAGE && subscription[i+1] == END_MESSAGE)
        {

            for (int j = 0; j < strlen(sensorsList); j++)
            {
                interpretedMessage[temp] = sensorsList[j];
                temp++;
            }
            
        }
        else if (subscription[i] == ALL_SPIECIES_MESSAGE)
        {

            if (subscription[i+1] == ALL_SENSORS_MESSAGE)
            {
                for (int spiecesI = 0; spiecesI < strlen(spiecesList); spiecesI++)
                {
                    interpretedMessage[temp] = spiecesList[spiecesI];
                    temp++;

                    for (int sensorI = 0; sensorI < strlen(sensorsList); sensorI++)
                    {
                        interpretedMessage[temp] = sensorsList[sensorI];
                        temp++;
                    }
                    interpretedMessage[temp] = END_MESSAGE;
                    temp++;
                }
                
                i += 2;

            }
            else
            {
                int k;

                for (int l = 0; l < strlen(spiecesList); l++)
                {
                    interpretedMessage[temp] = spiecesList[l];
                    temp++;

                    for (k = i + 1; subscription[k] != END_MESSAGE; k++)
                    {
                        interpretedMessage[temp] = subscription[k];
                        temp++;
                    }

                    interpretedMessage[temp] = END_MESSAGE;
                    temp++;
                }

                i = k;
            }
        }
        else
        {
            interpretedMessage[temp] = subscription[i];
            temp++;
        }
    }

    return interpretedMessage;
}