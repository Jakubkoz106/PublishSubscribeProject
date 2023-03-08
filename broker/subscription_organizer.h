
#ifndef SUBSCRIPTION_ORGANIZER_H_
#define SUBSCRIPTION_ORGANIZER_H_
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include<stdbool.h>
#include <netinet/in.h>
 
/**
 * @brief Structur linked list to store subscription.
 * 
 */
struct subscription_message_list 
{
    unsigned char data;
    struct subscription_message_list* next;
};

/**
 * @brief Add new subscription to list.
 * 
 * @param head_ref list of subscription
 * @param new_data new subscription
 */
void push_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char new_data);

/**
 * @brief Delete subscription from list.
 * 
 * @param head_ref list of subscription
 * @param key value of subscription to delete
 */
void delete_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char key);

/**
 * @brief Get information if specific subscription is in list.
 * 
 * @param head_ref list of subscription
 * @param key value of subscription
 * @return true if subscription is in list 
 * @return false if subscription is not in list
 */
bool get_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char key);


/**
 * @brief Structur used to store type with list of subscription.
 * 
 */
struct subscription_map
{
    unsigned char type;
    struct subscription_message_list* subscription_message_list;
};

/**
 * @brief Structur linked list to store subscription maps.
 * 
 */
struct subscription_map_list 
{
    struct subscription_map data; 
    struct subscription_map_list* next;
};

/**
 * @brief Add new subscription map.
 * 
 * @param head_ref subscription map list
 * @param new_data subscription map to be added 
 */
void push_subscription_map_list_element(struct subscription_map_list** head_ref, struct subscription_map new_data);

/**
 * @brief Delete subscription map element.
 * 
 * @param head_ref subscription map list
 * @param key species of animal which determinate subscription map list
 */
void delete_subscription_map_list_element(struct subscription_map_list** head_ref, unsigned char key);

/**
 * @brief Get subscripton map list element.
 * 
 * @param head_ref subscription map list
 * @param species_of_animal species of animal which determinate element
 * @return struct subscription_map* subscription map
 */
struct subscription_map* get_subscription_map_list_element(struct subscription_map_list** head_ref, unsigned char type);

/**
 * @brief Structur used to store socket adress with subsription map list.
 * 
 */
struct subscriber
{
    struct sockaddr_in sockaddr_in;
    struct subscription_map_list* subscription_map_list;
};

/**
 * @brief Structur linked list to store subsribers.
 * 
 */
struct subscribers_list
{
    struct subscriber data;
    struct subscribers_list* next;
};

/**
 * @brief Add new subscriber.
 * 
 * @param head_ref subscribers list
 * @param new_data new subscriber
 */
void push_subscribers_list_element(struct subscribers_list** head_ref, struct subscriber new_data);

/**
 * @brief Delete subscriber form list of subscribers.
 * 
 * @param head_ref list of subscribers
 * @param sin_port sin_port which determinate subscriber
 */
void delete_subscribers_list_element(struct subscribers_list** head_ref, unsigned short sin_port);

/**
 * @brief Print all elements of subscribers list. 
 * 
 * @param node subscribers list
 */
void print_subscribers_list_elements(struct subscribers_list* node);

/**
 * @brief Get subscriber from subscribers list.
 * 
 * @param head_ref subscribers list
 * @param sockaddr_in it determinates subscriber
 * @return struct subscriber* searched subscriber
 */
struct subscriber* get_subscribers_list_element(struct subscribers_list** head_ref, struct sockaddr_in sockaddr_in);

/**
 * @brief Delete subscriber from subscribers list if has no subscription.
 * 
 * @param subscribers_list subscribers list
 * @param subscriber analyzed subscriber
 */
void delete_empty_subscriber(struct subscribers_list** subscribers_list, struct subscriber subscriber);

/**
 * @brief Get subscribers list from other subscribers list which contain given type and subscription.
 * 
 * @param subscribers_list subscribers list to analyze
 * @param type analyzed type
 * @param subscription analyzed subscription  
 * @return struct subscribers_list* new subscribers list  
 */
struct subscribers_list* match_subscriber_type_subscription(struct subscribers_list* subscribers_list, unsigned char type, unsigned char subscription);

#endif