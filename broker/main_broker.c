
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
#include "subscription_organizer.h"

#define BROKER_PORT "1111"
#define BROKER_IP "192.168.181.5"
#define MAX_BUFF 64
#define REPORT_PERIOD_TIME 10000

int number_of_recived_message_from_publisher = 0;
int number_of_recived_subscription_message = 0;
int number_of_recived_unsubscription_message = 0;
int number_of_matched_message = 0;

int main(int argc, char* argv[])
{
    unsigned char mip_str[INET_ADDRSTRLEN];

    struct addrinfo h, *r=NULL;
    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family=AF_INET; 
    h.ai_socktype=SOCK_DGRAM;

    int getaddrinfo_status;
    if((getaddrinfo_status = getaddrinfo(BROKER_IP, BROKER_PORT, &h, &r)) != 0) 
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

    unsigned char message[MAX_BUFF];
    struct sockaddr_in c;
    int c_len = sizeof(c);
    int select_status;
    fd_set read_fds;
    FD_ZERO(&read_fds);
    
    struct timeval tv_select;
    
    uint32_t number_of_miliseconds = REPORT_PERIOD_TIME * 1000;
    uint32_t last_report_time = 0;
    struct subscribers_list* subscribers_list = NULL;

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
                
                int result = recvfrom(s, message, MAX_BUFF, 0,  (struct sockaddr*) &c, &c_len);
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

                    //PUBLISHER MESSAGE
                    if (message[0] == PUBLISHER) 
                    {
                        number_of_recived_message_from_publisher++;
                        struct subscribers_list* subscribers_to_sent = match_subscriber_type_subscription(subscribers_list, message[1], message[2]);
                        
                        while (subscribers_to_sent != NULL)
                        {
                            int sendto_message_status = sendto(s, message, strlen(message), 0, (const struct sockaddr *) &subscribers_to_sent->data, c_len);
                        
                            if (sendto_message_status > 0) {
                                number_of_matched_message++;
                            }
                            else if(sendto_message_status < 0) {
                                printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), strerror(errno), __FILE__, __LINE__);
                            }

                            subscribers_to_sent = subscribers_to_sent->next;
                        }

                        free(subscribers_to_sent);

                    }
                    //CLIENT SUBSCRIBE
                    else if (message[0] == CLIENT_SUBSCRIBE) 
                    {
                        number_of_recived_subscription_message++;
                        struct subscriber* existing_subscriber = get_subscribers_list_element(&subscribers_list, c);
                        
                        if (existing_subscriber == NULL)
                        {

                            struct subscription_map_list* subscription_map_list = NULL;
                            struct subscriber subscriber;

                            subscriber.sockaddr_in = c;
                            subscriber.subscription_map_list = subscription_map_list;

                            int temp = 1;

                            for (int i = 1; i < sizeof(message); i++)
                            {
                                if (message[i] == END_MESSAGE)
                                {
                                    char type = message[temp];
                                    struct subscription_map* existing_subscription_map = get_subscription_map_list_element(&subscriber.subscription_map_list, type);

                                    if (existing_subscription_map == NULL)
                                    {
                                        struct subscription_message_list* subscription_message_list = NULL;
                                        struct subscription_map subscription_map;


                                        temp++;
                                        for(temp; temp < i; temp++) 
                                        {
                                            push_subscription_message_list_element(&subscription_message_list, message[temp]);
                                        }

                                        subscription_map.type = type;
                                        subscription_map.subscription_message_list = subscription_message_list;
                                        
                                        push_subscription_map_list_element(&subscriber.subscription_map_list, subscription_map);
                                    }
                                    else
                                    {
                                        temp++;
                                        for(temp; temp < i; temp++) 
                                        {
                                            if (!get_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]))
                                            {
                                                push_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]);    
                                            }
                                        }
                                    }

                                    temp++;

                                }
                            }
                            
                            push_subscribers_list_element(&subscribers_list, subscriber);
                        }
                        else
                        {
                            int temp = 1;
                            for (int i = 1; i < sizeof(message); i++)
                            {
                                if (message[i] == END_MESSAGE)
                                {
                                    char type = message[temp];
                                    struct subscription_map* existing_subscription_map = get_subscription_map_list_element(&existing_subscriber->subscription_map_list, type);

                                    if (existing_subscription_map == NULL)
                                    {
                                        struct subscription_message_list* subscription_message_list = NULL;
                                        struct subscription_map subscription_map;


                                        temp++;
                                        for(temp; temp < i; temp++) 
                                        {
                                            push_subscription_message_list_element(&subscription_message_list, message[temp]);
                                        }

                                        subscription_map.type = type;
                                        subscription_map.subscription_message_list = subscription_message_list;
                                        
                                        push_subscription_map_list_element(&existing_subscriber->subscription_map_list, subscription_map);
                                    }
                                    else
                                    {
                                        temp++;
                                        for(temp; temp < i; temp++) 
                                        {
                                            if (!get_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]))
                                            {
                                                push_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]);    
                                            }
                                        }
                                    }

                                    temp++;
                                }
                            }
                        }
                    }
                    //CLIENT UNSUBSCRIBE
                    else if (message[0] == CLIENT_UNSUBSCRIBE) 
                    {
                        number_of_recived_unsubscription_message++;
                        struct subscriber* existing_subscriber = get_subscribers_list_element(&subscribers_list, c);

                        if (existing_subscriber == NULL)
                        {
                            printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), "Client wanted to unsubscribe but he is not registered", __FILE__, __LINE__);
                        }
                        else
                        {
                            int temp = 1;
                            for (int i = 1; i < sizeof(message); i++)
                            {
                                if (message[i] == END_MESSAGE)
                                {
                                    char type = message[temp];
                                    struct subscription_map* existing_subscription_map = get_subscription_map_list_element(&existing_subscriber->subscription_map_list, type);

                                    if (existing_subscription_map != NULL)
                                    {
                                        temp++;
                                        for(temp; temp < i; temp++) 
                                        {
                                            if (get_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]))
                                            {
                                                delete_subscription_message_list_element(&existing_subscription_map->subscription_message_list, message[temp]);    
                                            }
                                        }
                                    }

                                    temp++;
                                }
                            }
                            delete_empty_subscriber(&subscribers_list, *existing_subscriber);
                        }
                    }
                    //UNRECOGNIZED MESSAGE
                    else 
                    {
                        printf("%s ERROR - %s (%s:%d)\n", getCurrentTime(), "Invalid argument for message type", __FILE__, __LINE__);
                    }

                    memset(&message, 0, MAX_BUFF);
                    FD_CLR(s, &read_fds);
                }
            }
        }

        if (getTimeStamp() - last_report_time >= number_of_miliseconds)
        {
            last_report_time = getTimeStamp();
            printf("---------------------------------------------------- \n");
            printf("%s\n\n", getCurrentTime());
            print_subscribers_list_elements(subscribers_list);
            printf("Number of recived message from publisher: %d\n", number_of_recived_message_from_publisher);
            printf("Number of recived subscription message: %d\n", number_of_recived_subscription_message);
            printf("Number of recived unsubscription message: %d\n", number_of_recived_unsubscription_message);
            printf("Number of matched message (send to subscriber): %d\n\n", number_of_matched_message);
        }
    }

    free(subscribers_list);
    freeaddrinfo(r);
    close(s);
    return 0;
}