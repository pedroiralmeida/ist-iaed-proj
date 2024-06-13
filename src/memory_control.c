#include "header.h"
/*
Frees a reservation and his reservation code.
*/
void free_r(Reservation **r) {
    free((*r)->r_code);
    free(*r); 
    *r = NULL;  
}
/*
Frees all the components of a r_node.
*/
void destroy_node(r_node **to_remove) {
    free((*to_remove)->r->r_code);
    free((*to_remove)->r);
    free((*to_remove));
    *to_remove = NULL;
}
/*
Frees all the reservations in a list and sets it to NULL.
*/
void destroy_list(r_node *root) {
    while (root) {
        r_node *aux = root;
        root = root->next;
        destroy_node(&aux);
    }
}
/*
Frees everything in the hashtable.
*/
void destroy_hashtable() {
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        while(hashtable[i]) {
            Hash_flight *aux = hashtable[i];
            if (aux->flight->r_list  != NULL) 
                destroy_list(aux->flight->r_list);
            hashtable[i] = hashtable[i]->next;
            free(aux->flight);
            free(aux);
        }
        
}
/*
Checks if there is no more memory after a Reservation memory alocation.
*/
void memcheck_reserv(Reservation *reserv) {
    if (reserv == NULL) {
        puts("No memory");
        free(reserv);
        destroy_hashtable();
        exit(1);
    }
}
/*
Checks if there is no more memory after a reservation code memory alocation.
*/
void memcheck_r_code(Reservation *r, char *reserv_code) {
    if (reserv_code == NULL) {
        puts("No memory");
        free(reserv_code);
        free(r);
        destroy_hashtable();
        exit(1);
    }
}
/*
Checks if there is no more memory after a r_node memory alocation.
*/
void memcheck_node(r_node *node) {
    if (node == NULL) {
        puts("No memory");
        free(node);
        destroy_hashtable();
        exit(1);
    }
}
/*
Checks if there is no more memory after a Hash_flight memory alocation.
*/
void memcheck_hash_f(Hash_flight *h_f) {
    if (h_f == NULL) {
        puts("No memory");
        free(h_f);
        destroy_hashtable();
        exit(1);
    }
}
/*
Checks if there is no more memory after a Flight memory alocation.
*/
void memcheck_flight(Hash_flight *h_f, Flight *f) {
    if (f == NULL) {
        puts("No memory");
        free(f);
        free(h_f);
        destroy_hashtable();
        exit(1);
    }
}


