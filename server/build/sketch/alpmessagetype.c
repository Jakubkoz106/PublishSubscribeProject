#line 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alpmessagetype.c"
#include "alpmessagetype.h"

unsigned char clientUnSubscribe()
{
    return 0b01000000;
}

unsigned char clientSubscribe()
{
    return 0b10000000;
}

unsigned char publisher()
{
    return 0b11000000;
}

unsigned char endMessage()
{
    return 0b00001111;
}