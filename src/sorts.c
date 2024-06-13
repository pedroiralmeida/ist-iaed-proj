#include "header.h"
#include "sorts.h"
#include "conv_date_time.h"
#include "memory_control.h"
/*
Bubblesort based function that sorts an array of airports based on their id.
*/
void Bubblesort_airports(Airport a[]) {
    int i, j;
    bool done = FALSE;

    for (i = 0; i < len_airports; i++) {
        done = TRUE;
        for (j = 0; j < len_airports - 1 - i; j++)
            if (strcmp(a[j + 1].id, a[j].id) < 0) {
                swap_airps(a[j], a[j + 1]);
                done = FALSE; 
            }
        /* If there is no swaps the array is already sorted */
        if (done) break;
    }
}
/* 
Sorts flights according to their date and time of departure/arrival.
*/
void Bubblesort_flights(Flight fs[], int num_flights) {
    int i, j;
    bool done = FALSE;

    for (i = 0; i < num_flights; i++) {
        done = TRUE;
        for (j = 0; j < num_flights - 1 - i; j++) {
            if (date_to_days(fs[j + 1].date) < date_to_days(fs[j].date)) {
                swap_flights(fs[j], fs[j + 1]);
                done = FALSE;
            }
            else if (date_to_days(fs[j].date) == date_to_days(fs[j + 1].date)
                    && time_to_mins(fs[j + 1].time) < time_to_mins(fs[j].time))
            {
                swap_flights(fs[j], fs[j + 1]);
                done = FALSE;
            }
        }    
        if (done) break;
    }
}
/*
Inserts a r_node in the start of a list of reservations.
*/
void insert_start(r_node **r_list, Reservation *reserv) {
    r_node *new = (r_node*) malloc(sizeof(r_node));
    memcheck_node(new);
    new->r = reserv;

    new->next = *r_list;

    /* New is now the head of the list of reservations */
    *r_list = new;
}
/* 
Inserts a r_node after the given node in a list of reservations.
*/
void insert_after(r_node **reserv_node, Reservation *reserv) {
    r_node *new = (r_node*) malloc(sizeof(r_node));
    memcheck_node(new);
    new->r = reserv;


    new->next = (*reserv_node)->next;
    (*reserv_node)->next = new;
}
/*
Inserts a r_node in a sorted way in the reservation list of the given flight.
*/
void insert_sorted(Flight *f, Reservation *reserv) {
    r_node *curr = f->r_list;

    /* Inserts in the beginning if the list is empty or the r_code is minimum */ 
    if (curr == NULL || strcmp(reserv->r_code, curr->r->r_code) <= 0) {
        insert_start(&f->r_list, reserv);
        return;
    } 
    while (curr->next) { 
        if (strcmp(reserv->r_code, curr->next->r->r_code) <= 0) 
            break;
        curr = curr->next;
    }
    /* Inserts after the last inferior or equal id to the given */
    insert_after(&curr, reserv);
}
