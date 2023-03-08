# 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c"
# 2 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c" 2

unsigned char* allSpeciesList()
{
    unsigned char spiecesList[] = {0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101};

    unsigned char* messageToReturn = malloc(sizeof(spiecesList));

    for (int i = 0; i < sizeof(spiecesList); i++)
    {
        messageToReturn[i] = spiecesList[i];
    }


    return messageToReturn;
}

unsigned char* allSensorsList()
{
    unsigned char sensorsList[] = {0b00000001, 0b000000010, 0b00000011, 0b00000100, 0b00000101};

    unsigned char* messageToReturn = malloc(sizeof(sensorsList));

    for (int i = 0; i < sizeof(sensorsList); i++)
    {
        messageToReturn[i] = sensorsList[i];
    }

    return messageToReturn;
}

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
# 60 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c" 3 4
              __null
# 60 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c"
                  ;
    }
}

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
# 88 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c" 3 4
              __null
# 88 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\alp.c"
                  ;
    }
}
# 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino"
# 2 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2
# 3 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2
# 4 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2
# 5 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2
# 6 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2
# 7 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\publisher\\main_server.ino" 2






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
unsigned char animal = 0b00000001;
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
    unsigned int localPort = 1111;
    Udp.begin(localPort);

}

//unsigned long period_time = 5000;
//unsigned long current_time = 0;
//unsigned long saved_time = 0;

void sendMeasure(char* message_to_send){
    Udp.beginPacket(address_ip, 1111);
    int s=Udp.write(message_to_send, strlen(message_to_send));
    Udp.endPacket();
}

void loop(){
        char message_to_send[64];
        if(outputTemperature != ZsutAnalog0Read()){
            outputTemperature = ZsutAnalog0Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c", 0b11000000, animal, 0b00000001, outputTemperature & 0xFF, outputTemperature >> 8);
            sendMeasure(message_to_send);

        }else if(outputHumidity != ZsutAnalog1Read()){
            outputHumidity = ZsutAnalog1Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c", 0b11000000, animal, 0b000000010, outputHumidity & 0xFF, outputHumidity >> 8);
            sendMeasure(message_to_send);

        }else if(outputLight != ZsutAnalog2Read()){
            outputLight = ZsutAnalog2Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c", 0b11000000, animal, 0b00000011, outputLight & 0xFF, outputLight >> 8);
            sendMeasure(message_to_send);

        }else if(outputOxygenation != ZsutAnalog3Read()){
            outputOxygenation = ZsutAnalog3Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c", 0b11000000, animal, 0b00000100, outputOxygenation & 0xFF, outputOxygenation >> 8);
            sendMeasure(message_to_send);

        }else if(outputCarbonDioxide != ZsutAnalog4Read()){
            outputCarbonDioxide = ZsutAnalog4Read();
            snprintf(message_to_send, 64, "%c%c%c%c%c", 0b11000000, animal, 0b00000101, outputCarbonDioxide & 0xFF, outputCarbonDioxide >> 8);
            sendMeasure(message_to_send);
        }

}
