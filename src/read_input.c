#include "header.h"
#include "memory_control.h"
/*
Reads the input of the data of a flight and inserts it in a flight.
*/
Flight readFlight() {
    Flight f;

    scanf("%s%s%s %d-%d-%d %d:%d %d:%d %d",
    f.flycode, f.dep_airp.id, f.arriv_airp.id,
    &f.date.day, &f.date.month, &f.date.year,
    &f.time.hours, &f.time.mins,
    &f.duration.hours, &f.duration.mins, &f.capacity);

    f.available_capacity = f.capacity;
    f.r_list = NULL;
    return f;
}

Reservation *readReservation(bool *insert) {
    char buffer[MAX_RESERV_CODE];
    Reservation *r = (Reservation*) malloc(sizeof(Reservation));
    memcheck_reserv(r);

    scanf("%s %d-%d-%d",
    r->flycode, &r->date.day, &r->date.month, &r->date.year);

    /* If the point is to print the reservations and
    not insert one into the system */
    if (getchar() == '\n') {
        *insert = FALSE;
        return r;
    }
    else {
        scanf("%s %d", buffer, &r->num_passengers);
        r->r_code = (char*) malloc(sizeof(char) * (strlen(buffer) + 1));
        memcheck_r_code(r, r->r_code);
        strcpy(r->r_code, buffer);
        return r;
    }
}

