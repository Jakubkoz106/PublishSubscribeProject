

#include "subscription_organizer.h"

void push_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char new_data)
{
    struct subscription_message_list* new_node
        = (struct subscription_message_list*)malloc(sizeof(struct subscription_message_list));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void delete_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char key)
{
    struct subscription_message_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return;
 
    prev->next = temp->next;
 
    free(temp);
}

bool get_subscription_message_list_element(struct subscription_message_list** head_ref, unsigned char key)
{
    struct subscription_message_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data == key) {
        return true;
    }
 
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return false;
 
    return true;
}


void push_subscription_map_list_element(struct subscription_map_list** head_ref, struct subscription_map new_data)
{
    struct subscription_map_list* new_node
        = (struct subscription_map_list*)malloc(sizeof(struct subscription_map_list));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}
 

void delete_subscription_map_list_element(struct subscription_map_list** head_ref, unsigned char key)
{
    struct subscription_map_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data.type == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    while (temp != NULL && temp->data.type != key) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return;
 
    prev->next = temp->next;
 
    free(temp);
}

struct subscription_map* get_subscription_map_list_element(struct subscription_map_list** head_ref, unsigned char species_of_animal)
{
    struct subscription_map_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data.type == species_of_animal) {
        return &(temp->data);
    }
 
    while (temp != NULL && temp->data.type != species_of_animal) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return NULL;
 
    return &(temp->data);
}

void push_subscribers_list_element(struct subscribers_list** head_ref, struct subscriber new_data)
{
    struct subscribers_list* new_node
        = (struct subscribers_list*)malloc(sizeof(struct subscribers_list));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void delete_subscribers_list_element(struct subscribers_list** head_ref, unsigned short sin_port)
{
    struct subscribers_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data.sockaddr_in.sin_port == sin_port) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    while (temp != NULL && temp->data.sockaddr_in.sin_port != sin_port) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return;
 
    prev->next = temp->next;
 
    free(temp);
}

void print_subscribers_list_elements(struct subscribers_list* node)
{
    if (node == NULL)
    {
        printf("No subcribers to print\n");
    }

    while (node != NULL) 
    {
        printf("Subscriber: %d\n", node->data.sockaddr_in.sin_port);


        struct subscription_map_list* subscription_map_list = node->data.subscription_map_list;
        while(subscription_map_list != NULL)
        {

            struct subscription_message_list* subscription_message_list = subscription_map_list->data.subscription_message_list;
            
            printf("Type %d subscription:\n", subscription_map_list->data.type);

            while (subscription_message_list != NULL)
            {
                printf(" %d,", subscription_message_list->data);
                subscription_message_list = subscription_message_list->next;
            }
            
            printf("\n");

            subscription_map_list = subscription_map_list->next;
        }

        printf("\n");
        node = node->next;
    }

    printf("\n");
}

struct subscriber* get_subscribers_list_element(struct subscribers_list** head_ref, struct sockaddr_in sockaddr_in)
{
    struct subscribers_list *temp = *head_ref, *prev;
 
    if (temp != NULL && temp->data.sockaddr_in.sin_port == sockaddr_in.sin_port) {
        return &(temp->data);
    }
 
    while (temp != NULL && temp->data.sockaddr_in.sin_port != sockaddr_in.sin_port) {
        prev = temp;
        temp = temp->next;
    }
 
    if (temp == NULL)
        return NULL;
 
    return &(temp->data);
}

void delete_empty_subscriber(struct subscribers_list** subscribers_list, struct subscriber subscriber)
{
    bool isEmptySubscriber = true;

    while (subscriber.subscription_map_list != NULL)
    {  
        if (subscriber.subscription_map_list->data.subscription_message_list != NULL)
        {
            isEmptySubscriber = false;
        }

        subscriber.subscription_map_list = subscriber.subscription_map_list->next;
    }
    
    if (isEmptySubscriber)
    {
        delete_subscribers_list_element(subscribers_list, subscriber.sockaddr_in.sin_port);
    }
    else
    {
        //printf("nothing to delete! \n");
    }
}

struct subscribers_list* match_subscriber_type_subscription(struct subscribers_list* subscribers_list, unsigned char type, unsigned char subscription)
{
    struct subscribers_list* subscribers_list_return = NULL;

    if (subscribers_list == NULL)
    {
        return subscribers_list_return;
    }

    while (subscribers_list != NULL)
    {
        struct subscription_map_list* subscription_map_list = subscribers_list->data.subscription_map_list;

        while(subscription_map_list != NULL)
        {   
            if (subscription_map_list->data.type == type)
            {
                struct subscription_message_list* subscription_message_list = subscription_map_list->data.subscription_message_list;

                while (subscription_message_list != NULL)
                {
                    if (subscription_message_list->data == subscription)
                    {
                        push_subscribers_list_element(&subscribers_list_return, subscribers_list->data);
                        break;
                    }

                    subscription_message_list = subscription_message_list->next;
                }

            }
            subscription_map_list = subscription_map_list->next;
        }

        subscribers_list = subscribers_list->next;
    }

    return subscribers_list_return;
}