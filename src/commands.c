#include "header.h"
#include "prints.h"
#include "sorts.h"
#include "conv_date_time.h"
#include "hashtable.h"
#include "errors.h"
#include "read_input.h"
#include "memory_control.h"

/*
Adds an airport to the system or generates an error.
*/
void cmd_a() {
    Airport airport;
    int i, len_id;

    /* [^\n] to stop saving characters when it finds the \n */
    scanf("%s%s %[^\n]", airport.id, airport.country, airport.city);

    len_id = strlen(airport.id);

    for (i = 0; i < len_id; i++)
        if (airport.id[i] < 'A' || airport.id[i] > 'Z') { 
            puts("invalid airport ID");
            return; 
        }
    for (i = 0; i < len_airports; i++)
        if (!strcmp(sys_airports[i].id, airport.id)) { 
            puts("duplicate airport");
            return;
        }       
    if (MAX_AIRPORTS == len_airports) {
        puts("too many airports");
        return;
    }
    else
        sys_airports[len_airports++] = airport;

    printf("airport %s\n", airport.id);
}
/* 
Lists all or some specified airports from the system, or generates an error
if a given airport does not exist.
*/
void cmd_l() {
    int i;
    bool found = FALSE;
    char id[LEN_ID];

    if (getchar() == '\n') /* Command l without arguments */
    {
        Bubblesort_airports(sys_airports); 

        for (i = 0; i < len_airports; i++)
            print_cmd_l(sys_airports[i]);
    }
    else /* Command l with arguments */
    {
        do {  
            scanf("%s", id);
            found = FALSE;
            for (i = 0; i < len_airports; i++)
                if (!strcmp(id, sys_airports[i].id)) {
                    print_cmd_l(sys_airports[i]);
                    found = TRUE;
                    break;
                }
            if (!found)                
                printf("%s: no such airport ID\n", id);

        } while (getchar() != '\n');
    }
}
/*
Adds a flight to the system, lists all flights in the system or 
generates an error.
*/
void cmd_v() {   
    Flight f;
    Flight *f_in_hash;

    if (getchar() == '\n')
        print_cmd_v();
    else
    {
        f = readFlight();
        f_in_hash = getflight(f.flycode, f.date);

        if (invalid_code(f.flycode))
            puts("invalid flight code");
        else if (f_in_hash != NULL)
            puts("flight already exists");
        else if (unexisting_airportID(f.dep_airp.id))
            printf("%s: no such airport ID\n", f.dep_airp.id);
        else if (unexisting_airportID(f.arriv_airp.id)) 
            printf("%s: no such airport ID\n", f.arriv_airp.id);
        else if (max_flights_reached())
            puts("too many flights");
        else if (invalid_date(f.date))
            puts("invalid date");
        else if (invalid_duration(f.duration))  
            puts("invalid duration");
        else if (invalid_capacity(f.capacity))
            puts("invalid capacity");
        else {
            sys_flights[len_flights++] = f;
            insert_hashtable(f);
        }
    }
}
/*
Lists the flights with departure from an airport.
*/
void cmd_p() {
    int i, j = 0, num_flights = 0;
    char id[LEN_ID];
    Flight flights_dep_airp[MAX_FLIGHTS];

    scanf("%s", id);

    for (i = 0; i < len_flights; i++)
        if (!strcmp(sys_flights[i].dep_airp.id, id)) {
            flights_dep_airp[j++] = sys_flights[i];
            num_flights++;
        }

    Bubblesort_flights(flights_dep_airp, num_flights);

    if (unexisting_airportID(id))
        printf("%s: no such airport ID\n", id);
    else
        print_cmd_p(flights_dep_airp, num_flights);
}
/*
Lists the flights with arrival to an airport.
*/
void cmd_c() {
    int i, j = 0, num_flights = 0;
    char id[LEN_ID];
    Flight flights_arriv_airp[MAX_FLIGHTS], f;

    scanf("%s", id);

    for (i = 0; i < len_flights; i++)
        if (!strcmp(sys_flights[i].arriv_airp.id, id)) {
            f = dep_to_arriv_time_date(sys_flights[i]);
            flights_arriv_airp[j++] = f;
            num_flights++;
        }

    /* Sorts the flights by their date and time of arrival */
    Bubblesort_flights(flights_arriv_airp, num_flights);
    
    if (unexisting_airportID(id))
        printf("%s: no such airport ID\n", id);            
    else
        print_cmd_c(flights_arriv_airp, num_flights);
}
/*
Updates the date of the system or generates an error if the given date is
invalid.
*/
void cmd_t() {
    Date date;

    scanf("%d-%d-%d", &date.day, &date.month, &date.year);

    if (invalid_date(date))
        puts("invalid date");       
    else {
        sys_date = date;
        printf("%02d-%02d-%04d\n", sys_date.day, sys_date.month, sys_date.year);
    }
}
/*
Adds a reservation to the system, or lists all the reservations of a flight.
*/
void cmd_r() {
    Reservation *r;
    bool insert = TRUE, done = FALSE;
    Flight *flight; 
    
    r = readReservation(&insert);
    flight = getflight(r->flycode, r->date);

    if (!insert)
    {
        if (invalid_date(r->date))
            puts("invalid date");
        else if (flight == NULL) 
            printf("%s: flight does not exist\n", r->flycode);
        else 
            print_cmd_r(r->flycode, r->date);
        free(r);
    }
    else
    {
        if (invalid_reserv_code(r->r_code)) 
            puts("invalid reservation code");
        else if (flight == NULL) 
            printf("%s: flight does not exist\n", r->flycode);
        else if (existing_revervation(r->flycode, r->r_code))
            printf("%s: flight reservation already used\n", r->r_code);
        else if (max_reservations_exceded(flight, r->num_passengers)) 
            puts("too many reservations");
        else if (invalid_date(r->date)) 
            puts("invalid date");
        else if (invalid_passenger_num(r->num_passengers)) 
            puts("invalid passenger number");
        else {
            r->flight = flight;
            insert_sorted(flight, r);
            flight->available_capacity -= r->num_passengers;            
            done = TRUE;
        }
        /* Needed to free the reservation if its not inserted into the system */
        if (!done)
            free_r(&r); 
    }
}  
/*
Deletes all the flights with a given flycode and their reservations or deletes
a specified reservation.
*/
void cmd_e() {
    char code[MAX_RESERV_CODE];
    bool found = FALSE;

    scanf("%s", code);
    /* If it is a reservation code */
    if (strlen(code) > MAX_FLY_CODE)
    {
        if (invalid_reserv_code(code)) {
            puts("not found"); 
            return;
        }
        find_reserv_to_delete(code, &found);
        if (!found)
            puts("not found");
    }
    /* If it is a flycode */
    else
    {
        if (invalid_code(code)) {
            puts("not found");
            return;
        }
        delete_flights(code, &found);
        if (!found)
            puts("not found");
    }    
}
