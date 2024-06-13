#include "header.h"
#include "conv_date_time.h"
/*
Transforms a date in a number of days.
*/
int date_to_days(Date date) {
    int i, days, passed_months_days = 0;
    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    /* Saves the number os days of passed months */
    for (i = 0; i < date.month - 1; i++)
        passed_months_days += month_days[i];

    days = date.year * NUM_DAYS_YEAR + passed_months_days + date.day; 
    return days;
}

/*
Transforms hours and mins in only mins.
*/
int time_to_mins(Time time) {
    int mins;

    mins = time.hours * NUM_MINS_HOUR + time.mins;

    return mins;
}

/* 
Transforms the date and time of departure of a flight in his date and time
of arrival.
*/
Flight dep_to_arriv_time_date(Flight f) {
    int sum_mins, last_day_month, new_hour;
    bool new_day = FALSE;
    int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    sum_mins = f.time.mins + f.duration.mins;
    new_hour = sum_mins / NUM_MINS_HOUR;
    f.time.mins = sum_mins % NUM_MINS_HOUR;
    f.time.hours += f.duration.hours + new_hour;

    if (f.time.hours >= NUM_HOURS_DAY) {
        f.time.hours -= NUM_HOURS_DAY;
        new_day = TRUE;
    }  

    last_day_month = month_days[f.date.month - 1];

    /* If a day has passed */
    if (new_day) {
        f.date.day++;
        if (f.date.day > last_day_month) {
            f.date.month++;
            f.date.day = 1;
            
            if (f.date.month > NUM_MONTHS) { 
                f.date.year++;
                f.date.month = 1;
            }
        } 
    }
    return f;
}