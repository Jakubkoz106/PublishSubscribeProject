
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include<stdbool.h>
#include "timer.h"
#include "alp_message_type.h"
#include "alp.h"

#define SUBSCRIBER_PORT "1111"
//#define SUBSCRIBER_PORT "2222"
//#define SUBSCRIBER_PORT "3333"
#define SUBSCRIBER_IP "192.168.181.3"

#define BROKER_PORT "1111"
#define BROKER_IP "192.168.181.5"


#define MAX_BUFF 64
#define MAX_BUFF_RECIVE 5


//CHANGE VALUE OF SUBSCRIPTION/UNSUBSCRIPTION AND TIME TO SEND UNSUBSCRIPTION
//TIME IN MS
#define SEND_UNSUBSCRIBE_MESSAGE_TIME 20000

unsigned char mySubscription[] = {CLIENT_SUBSCRIBE, SNAKE, OXYGENATION, END_MESSAGE, ALL_SPIECIES_MESSAGE, TEMPREATURE, END_MESSAGE, LIZARD, ALL_SENSORS_MESSAGE, END_MESSAGE, '\0'};
unsigned char myUnsubscription[] = {CLIENT_SUBSCRIBE, SNAKE, LIGHT, CARBONDIOXIDE, END_MESSAGE, SPIDER, ALL_SENSORS_MESSAGE, END_MESSAGE, '\0'};

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


int main(int argc, char* argv[])
{
    unsigned char* subscribe_message_to_send = interpretSubscriptionMessage(mySubscription);
    unsigned char* unsubscribe_message_to_send = interpretSubscriptionMessage(myUnsubscription);

    unsigned char mip_str[INET_ADDRSTRLEN];

    //SOCKET SUBSCRIBER
    struct addrinfo h, *r=NULL;
    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family=AF_INET; 
    h.ai_socktype=SOCK_DGRAM;

    int getaddrinfo_status;
    if((getaddrinfo_status = getaddrinfo(SUBSCRIBER_IP, SUBSCRIBER_PORT, &h, &r)) != 0) 
    {
        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
        return -1;
    }

    int s;
    if((s=socket(r->ai_family, r->ai_socktype, r->ai_protocol)) != -1) 
    {
        printf("%s Socket description: %i\n", getCurrentTime(), s);
    }
    else if (s == -1) 
    {
        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
        free(r);
        return -1;
    }

    int bind_status;
    if((bind_status = bind(s, r->ai_addr, r->ai_addrlen)) == 0) 
    {
        printf("%s Socket binded\n", getCurrentTime());
    }
    else if (bind_status != 0) {
        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
        free(r);
        close(s);
        return -1;
    }

    //SOCKET BROKER
    struct addrinfo h_broker, *r_broker=NULL;
    memset(&h_broker, 0, sizeof(struct addrinfo));
    h_broker.ai_family=AF_INET; 
    h_broker.ai_socktype=SOCK_DGRAM;

    int getaddrinfo_status_broker;
    if((getaddrinfo_status_broker = getaddrinfo(BROKER_IP, BROKER_PORT, &h_broker, &r_broker)) != 0) 
    {
        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
        return -1;
    }

    int s_broker;
    if((s_broker=socket(r_broker->ai_family, r_broker->ai_socktype, r_broker->ai_protocol)) != -1) 
    {
        printf("%s Socket description: %i\n", getCurrentTime(), s_broker);
    }
    else if (s_broker == -1) 
    {
        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
        free(r_broker);
        return -1;
    }

    //SEND SUBSCRIBE MESSAGE
    int sendto_message_status = sendto(s, subscribe_message_to_send, MAX_BUFF, 0, r_broker->ai_addr, r_broker->ai_addrlen);
        
    if (sendto_message_status > 0) {
        printf("%s Subscription message sent. \n", getCurrentTime());
    }


    //RECIVE MESSAGE FROM BROKER WITH DATA
    unsigned char message[MAX_BUFF];
    struct sockaddr_in c;
    int c_len = sizeof(c);
    int select_status;
    fd_set read_fds;
    FD_ZERO(&read_fds);
    
    struct timeval tv_select;

    //VARIABLE USED FOR TEST SENDING UNSUBSCRIBE MESSAGE
    uint32_t start = getTimeStamp();
    uint32_t number_of_miliseconds = SEND_UNSUBSCRIBE_MESSAGE_TIME * 1000;
    bool send_once = true;
    
    while(1) 
    {
        
        tv_select.tv_sec = 0;
        tv_select.tv_usec = 50000;

        FD_ZERO(&read_fds);
        FD_SET(s, &read_fds);

        select_status = select(s+1, &read_fds, NULL, NULL, &tv_select);
        
        if (select_status < 0) 
        {
            break;
        }
        else if (select_status > 0) 
        {
            if (FD_ISSET(s, &read_fds)) 
            {
                
                int result = recvfrom(s, message, MAX_BUFF_RECIVE, 0,  (struct sockaddr*) &c, &c_len);
                if (result == 0) 
                {
                    FD_CLR(s, &read_fds);
                    close(s);
                    break;
                }
                else if (result < 0) 
                {
                    printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
                    break;
                }
                else if (result > 0) 
                {
                    message[result]='\0';

                    if (message[0] == PUBLISHER)
                    {
                        uint16_t value = (uint8_t)message[3] | message[4] << 8;
                        printf("%s Spieces: %s \n Sensor: %d \n Value: %d\n \n", getCurrentTime(), getSpeciesString(message[1]),  getSensorString(message[2]), value);
                    }
                }
            }
        }


        if (getTimeStamp() - start >= number_of_miliseconds && send_once)
        {
            send_once = false;

            int sendto_message_status = sendto(s, unsubscribe_message_to_send, MAX_BUFF, 0, r_broker->ai_addr, r_broker->ai_addrlen);
        
            if (sendto_message_status > 0) {
                printf("%s Unsubscribe message sent. \n", getCurrentTime());
            }
        }
    }

    freeaddrinfo(r);
    close(s);
    return 0;

}