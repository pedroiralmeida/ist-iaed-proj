/*
* File: main.c
* Author: Pedro Inacio Rebelo Almeida
* Number: 104168
* Description: Program that consists in a system to manage flights, 
controlling departure and arrival airports, and reservations to the flights.
*/

#include "header.h"
#include "commands.h"
#include "read_input.h"
#include "memory_control.h"
#include "sorts.h"
#include "conv_date_time.h"
#include "errors.h"
#include "prints.h"
#include "hashtable.h"


/* Vector with the airports of the system */
Airport sys_airports[MAX_AIRPORTS];
int len_airports;

/* Vector with the flights of the system */
Flight sys_flights[MAX_FLIGHTS];
int len_flights;

/* Current date of the system */
Date sys_date = {1, 1, 2022};

/* Hashtable with flights */
Hash_flight *hashtable[HASH_SIZE] = {NULL};


/*
Executes a command given by the user.
*/
int main()
{
    char cmd;

    while (TRUE) {
        cmd = getchar();
        switch (cmd) {
            case 'a':
                cmd_a();
                break;
            case 'l':
                cmd_l();
                break;
            case 'v':
                cmd_v();
                break;
            case 'p':
                cmd_p();
                break;
            case 'c':
                cmd_c();                
                break; 
            case 't':
                cmd_t();
                break; 
            case 'r':
                cmd_r();
                break; 
            case 'e':
                cmd_e();
                break;
            case 'q':
                destroy_hashtable();
                return 0;
        } 
    }
    return 0;
} 


