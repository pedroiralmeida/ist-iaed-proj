#include "header.h"
#include "conv_date_time.h"
#include "hashtable.h"
/* 
Verifies if a date is invalid.
*/
bool invalid_date(Date date) {
    int sys_days, date_days;

    sys_days = date_to_days(sys_date);
    date_days = date_to_days(date);

    /* If it is a date from the past or more than 1 year into the future */
    if (date_days - sys_days < 0 || date_days - sys_days > NUM_DAYS_YEAR)
        return TRUE;
    
    return FALSE;
}
/* 
Verifies if a flycode is invalid.
*/
bool invalid_code(char code[]) {
    int i, len_code = strlen(code);
    
    /* If the code as more than 2 letter and 4 digits */
    if (len_code > 6)
        return TRUE;

    for (i = 0; i < len_code; i++) {
        if (i < 2 && (code[i] < 'A' || code[i] > 'Z'))
            return TRUE;
        /* If after the 2 characters there isn't a number between 1 and 9999*/
        else if (i >= 2 && (code[2] == '0' || code[i] > '9' || code[i] < '0'))
            return TRUE;
    }
    return FALSE;
}
/*
Verifies if an id of an airport does not exist in the sytem.
*/
bool unexisting_airportID(char id[]) {
    int i;

    for (i = 0; i < len_airports; i++)
        if (!strcmp(id, sys_airports[i].id))
            return FALSE;

    return TRUE;
}
/*
Verifies if the system has reaches its maximum number of flights.
*/
bool max_flights_reached() { return len_flights == MAX_FLIGHTS; }
/*
Verifies if a duration of a flight is invalid - if it has passed the 12 hour mark.
*/
bool invalid_duration(Time duration) {
    return time_to_mins(duration) > 12 * NUM_MINS_HOUR;
}
/*
Verifies if the capacity of a flight is invalid.
*/
bool invalid_capacity(int capacity) {
    return capacity < 10;
}
/*
Verifies if a reservation code is invalid.
*/
bool invalid_reserv_code(char reserv_code[]) {
    int i, len_code = strlen(reserv_code);

    if (len_code < MIN_RESERV_CODE)
        return TRUE;
    
    for (i = 0; i < len_code; i++) {
        if ((reserv_code[i] >= 'A' && reserv_code[i] <= 'Z') ||
            (reserv_code[i] >= '0' && reserv_code[i] <= '9'))
            continue;
        return TRUE;
    }
    return FALSE;
}
/*
Verifies if a reservation already exists in the system.
*/
bool existing_revervation(char flycode[], char reserv_code[]) {
    int index = hash(flycode);
    Hash_flight *curr = hashtable[index];
    /* Searches through all the possible flights that hold the reservation */
    while(curr) 
    {
        if (curr->flight->r_list != NULL) {
            r_node *curr_reserv = curr->flight->r_list;
            while (curr_reserv) {
                if (!strcmp(curr_reserv->r->r_code, reserv_code))
                    return TRUE;
                curr_reserv = curr_reserv->next;
             }
        }
        curr = curr->next;
    } 
    return FALSE;   
}
/*
Verifies if the addition of a reservation exceeds the maximum capacity of
passengers in a flight.
*/
bool max_reservations_exceded(Flight *f, int num_passengers) {
    return f->available_capacity - num_passengers < 0;
}
/*
Verifies if a passenger number is invalid.
*/
bool invalid_passenger_num(int num_passengers) { return num_passengers <= 0; }