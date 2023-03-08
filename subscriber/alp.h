#ifndef ALP_H_
#define ALP_H_

#include <stdlib.h>
#include <stddef.h>

//OPTIONS ALL
#define ALL_SPIECIES_MESSAGE 0b11111111
#define ALL_SENSORS_MESSAGE 0b11111111

//SPECIES OF ANIMAL
#define LIZARD 0b00000001
#define TURTLE 0b00000010
#define SNAKE 0b00000011
#define MOUSE 0b00000100
#define SPIDER 0b00000101

unsigned char* allSpeciesList();

//SENSORS
#define TEMPREATURE 0b00000001
#define HUMIIDITY 0b000000010
#define LIGHT 0b00000011
#define OXYGENATION 0b00000100
#define CARBONDIOXIDE 0b00000101

unsigned char* allSensorsList();

const char* getSpeciesString(unsigned char species);

const char* getSensorString(unsigned char sensor);

#endif