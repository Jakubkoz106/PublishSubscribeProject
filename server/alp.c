#include "alp.h"

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