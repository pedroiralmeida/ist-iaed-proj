#include "header.h"
#include "prints.h"
#include "conv_date_time.h"
#include "hashtable.h"
/*
Prints the id, city, country and number of flights with 
origin in an airport.
*/
void print_cmd_l(Airport a) {
    int i, num_flights = 0;

    for (i = 0; i < len_flights; i++) 
        /* Se houver um voo com origem no aeroporto */
        if (!strcmp(a.id, sys_flights[i].dep_airp.id))
            num_flights++;

    printf("%s %s %s %d\n",
    a.id, a.city, a.country, num_flights); 
}
/*
Prints the flycode, id of the departure and arrival airport, and date
and hour of departure of a flight.
*/
void print_cmd_v() {
    int i;

    for (i = 0; i < len_flights; i++)
        printf("%s %s %s %02d-%02d-%04d %02d:%02d\n",
        sys_flights[i].flycode, 
        sys_flights[i].dep_airp.id, sys_flights[i].arriv_airp.id,
        sys_flights[i].date.day, sys_flights[i].date.month, sys_flights[i].date.year,
        sys_flights[i].time.hours, sys_flights[i].time.mins);  
}
/*
Prints the flycode, id of the departure airport,
and date and time of departure of a number of flights.
*/
void print_cmd_p(Flight fs[], int num_flights) {
    int i;

    for (i = 0; i < num_flights; i++)
        printf("%s %s %02d-%02d-%04d %02d:%02d\n",
        fs[i].flycode, fs[i].arriv_airp.id,
        fs[i].date.day, fs[i].date.month, fs[i].date.year,
        fs[i].time.hours, fs[i].time.mins);
}
/*
Prints the flycode, id of the departure airport and date and time of
arrival of a flight.
*/
void print_cmd_c(Flight fs[], int num_flights) {
    int i;

    for (i = 0; i < num_flights; i++)
        printf("%s %s %02d-%02d-%04d %02d:%02d\n",
        fs[i].flycode, fs[i].dep_airp.id,
        fs[i].date.day, fs[i].date.month, fs[i].date.year,
        fs[i].time.hours, fs[i].time.mins);
}
/*
Prints the reservation code and the number of passengers of the reservations
of a flight.
*/
void print_cmd_r(char flycode[], Date date) {
    int index = hash(flycode);
    Hash_flight *hash_f = hashtable[index];

    while (hash_f) {
        if (!strcmp(hash_f->flight->flycode, flycode) &&
            date_to_days(hash_f->flight->date) == date_to_days(date))
        { 
            r_node *curr = hash_f->flight->r_list;
            while (curr) {
                printf("%s %d\n", curr->r->r_code, curr->r->num_passengers);
                curr = curr->next;
            }
            break; 
        }    
        hash_f = hash_f->next;
    }
}


