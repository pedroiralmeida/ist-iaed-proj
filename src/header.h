/* 
* File: header.h
* Author: Pedro Inacio Rebelo Almeida
* Description: Header of the project
*/

#ifndef _HEADER_H_
#define _HEADER_H_

/*
LIBRARIRES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
CONSTANTS
*/

#define LEN_ID 4
#define MAX_COUNTRY 31
#define MAX_CITY 51
#define MAX_AIRPORTS 40
#define MAX_INPUT 100000
#define MAX_FLIGHTS 30000
#define MAX_FLY_CODE 7
#define MAX_FLIGHT_DURATION 12
#define NUM_MONTHS 12
#define NUM_DAYS_YEAR 365 
#define NUM_MINS_HOUR 60 
#define NUM_HOURS_DAY 24 
#define MIN_RESERV_CODE 10 
#define MAX_RESERV_CODE 65535 
#define HASH_SIZE 24593

/*
MACRO
*/

/* Swaps 2 flights or airports in an array */
#define swap_airps(A, B) { Airport t = A; A = B; B = t; }
#define swap_flights(A, B) { Flight t = A; A = B; B = t; }


/*
ENUMS
*/

/* Defines FALSE as 0 and TRUE as 1 */
typedef enum {FALSE, TRUE} bool;


/*
STRUCTURES
*/

typedef struct {
    char id[LEN_ID];
    char country[MAX_COUNTRY];
    char city[MAX_CITY];

} Airport;

typedef struct {
    int hours;
    int mins;

} Time;

typedef struct {
    int day;
    int month;
    int year;

} Date;

typedef struct stru_r_node {
    struct reservation *r;
    struct stru_r_node *next;

} r_node;

typedef struct {
    char flycode[MAX_FLY_CODE];
    Airport arriv_airp;
    Airport dep_airp;
    Date date;
    Time time;
    Time duration;
    int capacity;
    int available_capacity;
    r_node *r_list;

} Flight;


typedef struct reservation {
    char flycode[MAX_FLY_CODE];
    Date date;
    char *r_code;
    int num_passengers;
    Flight *flight;

} Reservation;


typedef struct stru_hash_flight {
    Flight *flight;
    struct stru_hash_flight *next;

} Hash_flight;

/*
GLOBAL VARIABLES
*/

extern Airport sys_airports[];
extern int len_airports;
extern Flight sys_flights[];
extern int len_flights;
extern Date sys_date;
extern r_node *head;
extern Hash_flight *hashtable[];

#endif