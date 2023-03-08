#line 1 "c:\\Users\\Janek\\Desktop\\studia\\sem5\\PSIR\\Sosulski_Jan_Krzysztof\\projekt\\server\\alpmessagetype.h"
#ifndef ALPMESSAGETYPE_H_
#define ALPMESSAGETYPE_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

//message from client about unsubscribe
unsigned char clientUnSubscribe();

//message from client about subscribe
unsigned char clientSubscribe();

//message from node/publisher
unsigned char publisher();

//end one message about subscribtion '00000000'
unsigned char endMessage();

#endif