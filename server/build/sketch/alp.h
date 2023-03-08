#line 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alp.h"
#ifndef ALP_H_
#define ALP_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

//OPTIONS ALL
//subscribe all species '11111111'
unsigned char allSpecies();

//subscribe all measurements '11111111'
unsigned char allMeasurements();

//SPECIES OF ANIMAL
//subscribe/send Lizard
unsigned char lizard();

//subscribe/send Turtle
unsigned char turtle();

//subscribe/send Snake
unsigned char snake();

//subscribe/send Mouse
unsigned char mouse();

//subscribe/send Spider
unsigned char spider();

//SENSORS
//subscribe/send Tempreature
unsigned char tempreature();

//subscribe/send Humidity
unsigned char humidity();

//subscribe/send Light
unsigned char light();

//subscribe/send Oxygenation
unsigned char oxygenation();

//subscribe/send CarbonDioxide
unsigned char carbonDioxide();

//const char* getSpeciesString(const unsigned char species);

//const char* getSensorString(const unsigned char sensor);

#endif