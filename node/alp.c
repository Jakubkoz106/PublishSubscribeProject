#include "alp.h"

/**
 * @brief Return list of all animal spieces.
 * 
 * @return unsigned* all animal spieces
 */
unsigned char* allSpeciesList()
{
    unsigned char spiecesList[] = {LIZARD, TURTLE, SNAKE, MOUSE,  SPIDER, '\0'};

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
unsigned char* allSensorsList()
{
    unsigned char sensorsList[] = {TEMPREATURE, HUMIIDITY, LIGHT, OXYGENATION,  CARBONDIOXIDE, '\0'};

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
const char* getSpeciesString(unsigned char species)
{
    if (species == LIZARD)
    {
        return "Lizard";
    }
    else if (species == TURTLE)
    {
        return "Turtle";
        /* code */
    }
    else if (species == SNAKE)
    {
        return "Snake";
        /* code */
    }
    else if (species == MOUSE)
    {
        return "Mouse";
        /* code */
    }
    else if (species == SPIDER)
    {
        return "Spider";
        /* code */
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief Get readable sensor name from alp message.
 * 
 * @param sensor alp message
 * @return const char* readable name
 */
const char* getSensorString(unsigned char sensor)
{
    if (sensor == TEMPREATURE)
    {
        return "Tempreature";
    }
    else if (sensor == HUMIIDITY)
    {
        return "Humidity";
    }
    else if (sensor == LIGHT)
    {
        return "Light";
    }
    else if (sensor == OXYGENATION)
    {
        return "Oxygenation";
    }
    else if (sensor == CARBONDIOXIDE)
    {
        return "Carbon Dioxide";
    }
    else
    {
        return NULL;
    }
}