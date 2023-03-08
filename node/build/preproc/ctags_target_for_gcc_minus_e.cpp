# 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
/**

 * @file alp.c

 * @author Jan Sosulski, Jakub Kozłowski, Małgorzata Olech

 * @brief 

 * @version 0.1

 * @date 2023-01-13

 */
# 9 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
# 10 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c" 2

/**

 * @brief Return list of all animal spieces.

 * 

 * @return unsigned* all animal spieces

 */
# 16 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
unsigned char* allSpeciesList()
{
    unsigned char spiecesList[] = {0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, '\0'};

    unsigned char* messageToReturn = malloc(sizeof(spiecesList));

    for (int i = 0; i < sizeof(spiecesList); i++)
    {
        messageToReturn[i] = spiecesList[i];
    }


    return messageToReturn;
}

/**

 * @brief Return list of all sensors.

 * 

 * @return unsigned* all sensors

 */
# 36 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
unsigned char* allSensorsList()
{
    unsigned char sensorsList[] = {0b00000001, 0b000000010, 0b00000011, 0b00000100, 0b00000101, '\0'};

    unsigned char* messageToReturn = malloc(sizeof(sensorsList));

    for (int i = 0; i < sizeof(sensorsList); i++)
    {
        messageToReturn[i] = sensorsList[i];
    }

    return messageToReturn;
}

/**

 * @brief Get readable name of spieces from alp message.

 * 

 * @param species alp message

 * @return const char* readable name

 */
# 56 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
const char* getSpeciesString(unsigned char species)
{
    if (species == 0b00000001)
    {
        return "Lizard";
    }
    else if (species == 0b00000010)
    {
        return "Turtle";
        /* code */
    }
    else if (species == 0b00000011)
    {
        return "Snake";
        /* code */
    }
    else if (species == 0b00000100)
    {
        return "Mouse";
        /* code */
    }
    else if (species == 0b00000101)
    {
        return "Spider";
        /* code */
    }
    else
    {
        return 
# 84 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c" 3 4
              __null
# 84 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
                  ;
    }
}

/**

 * @brief Get readable sensor name from alp message.

 * 

 * @param sensor alp message

 * @return const char* readable name

 */
# 94 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
const char* getSensorString(unsigned char sensor)
{
    if (sensor == 0b00000001)
    {
        return "Tempreature";
    }
    else if (sensor == 0b000000010)
    {
        return "Humidity";
    }
    else if (sensor == 0b00000011)
    {
        return "Light";
    }
    else if (sensor == 0b00000100)
    {
        return "Oxygenation";
    }
    else if (sensor == 0b00000101)
    {
        return "Carbon Dioxide";
    }
    else
    {
        return 
# 118 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c" 3 4
              __null
# 118 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\alp.c"
                  ;
    }
}
# 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino"
# 2 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2
# 3 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2
# 4 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2
# 5 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2
# 6 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2
# 7 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino" 2





ZsutEthernetUDP Udp;
ZsutIPAddress address_ip=ZsutIPAddress(192,168,181,5);

//#define MY_PUBLISHER_PORT 1111
//#define MY_PUBLISHER_PORT 2222

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
unsigned char animal = 0b00000011;
//unsigned char animal = MOUSE;
//unsigned char animal = SPIDER;

//SUBSCIPTION
unsigned char mySubscription[] = {0b10000000, 0b11111111, 0b11111111, 0b11111110, '\0'};

unsigned char myUnsubscription[] = {0b10000000, 0b00000011, 0b11111111, 0b11111110, 0b00000101, 0b00000100, 0b00000011, 0b11111110, '\0'};
unsigned char myAddsubscription[] = {0b10000000, 0b00000011, 0b11111111, 0b11111110, 0b00000101, 0b00000100, 0b00000011, 0b11111110, '\0'};

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
    unsigned int localPort = 3333;
    Udp.begin(localPort);

    start_time = ZsutMillis();

    //SEND SUBSCRIBE/UNSUBSCRIBE OR JUST START WORKING
    state = stateEnum::SUBSCRIBE;
}

void sendMeasure(char* message_to_send){
    Udp.beginPacket(address_ip, 1111);
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

        Udp.beginPacket(address_ip, 1111);
        int r=Udp.write(subscribe_message_to_send, 64);
        Udp.endPacket();
        Serial.println("Subscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::UNSUBSCRIBE)
    {
        unsigned char* unsubscribe_message_to_send = interpretSubscriptionMessage(myUnsubscription);

        Udp.beginPacket(address_ip, 1111);
        int r=Udp.write(unsubscribe_message_to_send, 64);
        Udp.endPacket();
        Serial.println("Unsubscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::ADDSUBSRIPTION)
    {
        unsigned char* addsubscribe_message_to_send = interpretSubscriptionMessage(myAddsubscription);

        Udp.beginPacket(address_ip, 1111);
        int r=Udp.write(addsubscribe_message_to_send, 64);
        Udp.endPacket();
        Serial.println("Add subscription message sent. \n");

        state = stateEnum::WORKING;
    }
    else if (state == stateEnum::WORKING)
    {
        char message_to_send[64];
        if(outputTemperature != ZsutAnalog0Read()){
            outputTemperature = ZsutAnalog0Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c%c", 0b11000000, animal, 0b00000001, outputTemperature & 0xFF, outputTemperature >> 8, 0b11111110);
            sendMeasure(message_to_send);

        }else if(outputHumidity != ZsutAnalog1Read()){
            outputHumidity = ZsutAnalog1Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c%c", 0b11000000, animal, 0b000000010, outputHumidity & 0xFF, outputHumidity >> 8, 0b11111110);
            sendMeasure(message_to_send);

        }else if(outputLight != ZsutAnalog2Read()){
            outputLight = ZsutAnalog2Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c%c", 0b11000000, animal, 0b00000011, outputLight & 0xFF, outputLight >> 8, 0b11111110);
            sendMeasure(message_to_send);

        }else if(outputOxygenation != ZsutAnalog3Read()){
            outputOxygenation = ZsutAnalog3Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c%c", 0b11000000, animal, 0b00000100, outputOxygenation & 0xFF, outputOxygenation >> 8, 0b11111110);
            sendMeasure(message_to_send);

        }else if(outputCarbonDioxide != ZsutAnalog4Read()){
            outputCarbonDioxide = ZsutAnalog4Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c%c", 0b11000000, animal, 0b00000101, outputCarbonDioxide & 0xFF, outputCarbonDioxide >> 8, 0b11111110);
            sendMeasure(message_to_send);
        }

        int packetSize=Udp.parsePacket();

        if(packetSize)
        {
            unsigned char recived_message[6];
            memset(&recived_message[0], 0, sizeof(recived_message));

            int r=Udp.read(recived_message, sizeof(recived_message));

            if (recived_message[0] == 0b11000000)
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
# 199 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\node\\main_server.ino"
unsigned char* interpretSubscriptionMessage(unsigned char subscription[])
{
    unsigned char* interpretedMessage = malloc(64);
    unsigned char* sensorsList = allSensorsList();
    unsigned char* spiecesList = allSpeciesList();

    int temp = 0;

    for (int i = 0; i < strlen(subscription); i++)
    {

        if (subscription[i] == 0b11111111 && subscription[i+1] == 0b11111110)
        {

            for (int j = 0; j < strlen(sensorsList); j++)
            {
                interpretedMessage[temp] = sensorsList[j];
                temp++;
            }

        }
        else if (subscription[i] == 0b11111111)
        {

            if (subscription[i+1] == 0b11111111)
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
                    interpretedMessage[temp] = 0b11111110;
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

                    for (k = i + 1; subscription[k] != 0b11111110; k++)
                    {
                        interpretedMessage[temp] = subscription[k];
                        temp++;
                    }

                    interpretedMessage[temp] = 0b11111110;
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
