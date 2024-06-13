#include "header.h"
#include "conv_date_time.h"
#include "memory_control.h"

/*
Hash function for a flycode.
*/
int hash(char *flycode)
{
    int h, a = 31415, b = 27183;
    for (h = 0; *flycode != '\0'; flycode++, a = a*b % (HASH_SIZE-1))
        h = (a*h + *flycode) % HASH_SIZE;
    return h;
}
/*
Inserts a flight in the hashtable.
*/
void insert_hashtable(Flight f) {
    int index = hash(f.flycode);
    Hash_flight *new = (Hash_flight*) malloc(sizeof(Hash_flight));
    Flight *new_f = (Flight*) malloc(sizeof(Flight));
    memcheck_hash_f(new);
    memcheck_flight(new, new_f);

    *new_f = f,
    new->flight = new_f; 
    new->next = hashtable[index];
    hashtable[index] = new;
}
/*
Finds and returns a flight in the hashtable. Returns NULL if its not found.
*/
Flight *getflight(char flycode[], Date date) {
    int index = hash(flycode);
    Hash_flight *curr = hashtable[index];

    while(curr) {
        if (!strcmp(curr->flight->flycode, flycode) && 
            date_to_days(curr->flight->date) == date_to_days(date))
            return curr->flight;
        curr = curr->next;
    }
    return NULL;
}
/*
Finds and deletes a reservation.
*/
bool find_and_delete_reserv(r_node **r_lst, char r_code[], bool *found) {
    r_node *temp;
    r_node *curr_reserv = *r_lst;

    /* If the wanted reservation its in the head of the list */
    if (!strcmp((*r_lst)->r->r_code, r_code)) {
        *found = TRUE;
        temp = *r_lst;
        (*r_lst)->r->flight->available_capacity += (*r_lst)->r->num_passengers;
        *r_lst = (*r_lst)->next;
        destroy_node(&temp);
        return TRUE;
    }
    while (curr_reserv->next) {
        if (!strcmp(curr_reserv->next->r->r_code, r_code)) {
            *found = TRUE;
            temp = curr_reserv->next;
            temp->r->flight->available_capacity += temp->r->num_passengers;
            curr_reserv->next = curr_reserv->next->next;
            destroy_node(&temp);
            return TRUE;
        }
        curr_reserv = curr_reserv->next;
    }
    return FALSE;
}
/*
Searches through the hashtable to find possible reservation lists with
the reservation code to be deleted and deletes it if founded.
*/
void find_reserv_to_delete(char r_code[], bool *found) {
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        if (hashtable[i] != NULL) {
            Hash_flight *curr = hashtable[i];
            while (curr) {
                if (curr->flight->r_list != NULL) {
                    if (find_and_delete_reserv(&curr->flight->r_list, r_code,
                        found))
                        return;
                }
                curr = curr->next;                
            }
        }
}
/*
Deletes all the flights with the given flycode and their reservations
from the hashtable.
*/
void delete_hflight(char flycode[]) {
    int index = hash(flycode);
    Hash_flight *curr = hashtable[index];
    Hash_flight *temp;

    while (curr->next) {
        if (!strcmp(curr->next->flight->flycode, flycode)) {
            temp = curr->next;
            if (temp->flight->r_list != NULL) 
                destroy_list(temp->flight->r_list);
            curr->next = curr->next->next;
            free(temp->flight);
            free(temp);
            temp = NULL;
        }
        else curr = curr->next;
    }
   if (!strcmp(hashtable[index]->flight->flycode, flycode)) {
        temp = hashtable[index];
        if (temp->flight->r_list != NULL)
            destroy_list(temp->flight->r_list);
        hashtable[index] = hashtable[index]->next;
        free(temp->flight);
        free(temp);
        temp = NULL;
    }
}
/*
Deletes the flights with the given flycode from the system.
*/
void delete_flights(char flycode[], bool *found) {
    int i = 0, new_len_flights = 0;
    *found = TRUE;
                                          
   for (i = 0; i < len_flights; i++) 
        /* Adds only the flights with an id different from the given */
       if (strcmp(sys_flights[i].flycode, flycode)) 
           sys_flights[new_len_flights++] = sys_flights[i];

    /* If all the flights have a different id than the given */
    if (new_len_flights == len_flights) {
        *found = FALSE;
        return;        
    }
    len_flights = new_len_flights;
    delete_hflight(flycode);
}
